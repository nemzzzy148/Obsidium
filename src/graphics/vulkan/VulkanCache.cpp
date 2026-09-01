//
// Created by Nemesis Verstraete on 29/07/2026.
//

#include "VulkanCache.h"
#include "VulkanPipeline.h"
#include "VulkanTexture.h"
#include "../../utils/Algorithm.h"
#include "../../utils/Logger.h"
#include "utils/Hash.h"

namespace obsidium::vulkan {
// === pipeline cache ===
VulkanPipelineCache::VulkanPipelineCache(VulkanDevice &device, VulkanSwapChain& swapChain, IDSystem<AssetID> *idSystem) :
        device(device), idSystem(idSystem), swapChain(swapChain) {

    // configure shader descriptor for without textures and with
    uniformSetLayout.descriptorSetLayout = std::make_unique<VulkanDescriptorSetLayout>(device);
    uniformSetLayout.pipelineLayout = std::make_unique<VulkanPipelineLayout>(device,
        *uniformSetLayout.descriptorSetLayout.get());

    textureSetLayout.descriptorSetLayout = std::make_unique<VulkanDescriptorSetLayout>(device, 32, 4096);
    textureSetLayout.pipelineLayout = std::make_unique<VulkanPipelineLayout>(device,
        *textureSetLayout.descriptorSetLayout.get());
}

VulkanPipeline& VulkanPipelineCache::getPipeline(const AssetID id) const {
    if (!pipelines.contains(id)) {
        LOG_ERROR("ID invalid, returning no material vulkan pipeline!");
        return *pipelines.begin()->second;
    }
    return *pipelines.at(id);
}

AssetID VulkanPipelineCache::allocatePipeline(std::vector<char> code, const bool requiresTextures) {
    const uint64_t hash = hash::fnv1a(code, requiresTextures);
    if (hashes.contains(hash)) return hashes.at(hash);

    AssetID id = idSystem->allocate();
    id.hash = hash;

    if (requiresTextures) {
        pipelines.try_emplace(id, std::make_unique<VulkanPipeline>(device, swapChain,
            *textureSetLayout.pipelineLayout, code));
    }
    else {
        pipelines.try_emplace(id, std::make_unique<VulkanPipeline>(device, swapChain,
            *uniformSetLayout.pipelineLayout, code));
    }
    hashes.try_emplace(hash, id);

    return id;
}

void VulkanPipelineCache::destroyPipeline(const AssetID id) {
    if (id == InvalidAssetID || !pipelines.contains(id)) {
        LOG_WARNING("failed to destroy vulkan pipeline, invalid asset id!");
        return;
    }
    pipelines.erase(id);
    hashes.erase(id.hash);
}


// === bindless manager ===
VulkanBindlessManager::VulkanBindlessManager(VulkanDevice &device, IDSystem<AssetID> *idSystem,
    const uint32_t maxTextures, const uint32_t maxSamplers) : device(device), idSystem(idSystem),
        maxTextures(maxTextures), maxSamplers(maxSamplers) {
    pool = std::make_unique<VulkanBindlessDescriptorPool>(device, maxSamplers, maxTextures);

    freeTextureIndices.reserve(maxTextures);
    for (uint32_t i = 0; i < freeTextureIndices.size(); i++) {
        freeTextureIndices[i] = i;
    }

    freeSamplerIndices.reserve(maxSamplers);
    for (uint32_t i = 0; i < freeSamplerIndices.size(); i++) {
        freeSamplerIndices[i] = i;
    }
}

AssetID VulkanBindlessManager::allocateTexture(VulkanTexture &texture, const uint64_t hash) {
    if (textureHashes.contains(hash)) return textureHashes.at(hash);
    if (texture.getSize() < 1) {
        LOG_ERROR("failed to create vulkan bindless descriptor sets for a texture because its size was 0.");
        return InvalidAssetID;
    }
    if (freeTextureIndices.empty()) {
        LOG_ERROR("texture vulkan usage limit of ", maxTextures, " textures exceeded! "
                                                          "Cannot allocate any more textures into the bindless set!");
        return InvalidAssetID;
    }

    const uint32_t index = freeTextureIndices.back();
    AssetID id = idSystem->allocate();
    id.hash = hash;

    sets->updateTextureSet(texture.getView(), index);
    textureIndices.try_emplace(id, index);
    textureHashes.try_emplace(hash, id);

    freeTextureIndices.pop_back();
    return id;
}

void VulkanBindlessManager::destroyTexture(const AssetID id) {
    if (id == InvalidAssetID || !textureIndices.contains(id)) {
        LOG_WARNING("failed to destroy vulkan texture descriptor, invalid asset id!");
        return;
    }
    freeTextureIndices.push_back(textureIndices.at(id));
    textureIndices.erase(id);
    textureHashes.erase(id.hash);
}

AssetID VulkanBindlessManager::allocateSampler(const SamplerState state) {
    if (samplerStates.contains(state)) return samplerStates.at(state);
    if (freeSamplerIndices.empty()) {
        LOG_ERROR("sampler vulkan usage limit of ", maxSamplers, "samplers exceeded! "
                                                          "Cannot allocate any more samplers into the sampler set");
        return InvalidAssetID;
    }

    const uint32_t index = freeSamplerIndices.back();
    const AssetID id = idSystem->allocate();
    samplers.try_emplace(id, std::make_unique<VulkanSampler>(device, state));
    sets->updateSamplerSet(samplers.at(id)->getHandle(), index);
    samplerStates.try_emplace(state, id);
    samplerIndices.try_emplace(id, index);

    freeSamplerIndices.pop_back();
    return id;
}

void VulkanBindlessManager::destroySampler(AssetID id) {
    if (!samplerIndices.contains(id)) {
        LOG_WARNING("failed to destroy vulkan sampler descriptor, invalid asset id!");
        return;
    }
    freeSamplerIndices.push_back(samplerIndices.at(id));
    samplerIndices.erase(id);

    const auto it = std::ranges::find_if(samplerStates, [&](const auto& pair) {
        return pair.second == id;
    });
    if (it != samplerStates.end()) {
        samplerStates.erase(it->first);
    }
}

// === uniform manager ===
VulkanUniformManager::VulkanUniformManager(VulkanDevice& device, IDSystem<AssetID>* idSystem, const uint32_t bufferSize,
                                           const uint32_t framesInFlight, const uint32_t maxAvailableDescriptorSets) :
        device(device), idSystem(idSystem), framesInFlight(framesInFlight),
        maxAvailableDescriptorSets(maxAvailableDescriptorSets), availableAllocatableSets(maxAvailableDescriptorSets)   {

    byteAlignment = device.getPhysicalDevice().getProperties().limits.minUniformBufferOffsetAlignment;
    createPool();
    createUniformBuffers(bufferSize);
}

AssetID VulkanUniformManager::allocateUniformBufferRegion(uint32_t size) {
    size = alignUp(byteAlignment, size);
    const auto it = std::ranges::find_if(freeUniformSpaces, [size](const auto& r) {
        return r.size >= size;
    });
    if (it == freeUniformSpaces.end()) {
        LOG_ERROR("failed to find space for material attributes in vulkan uniform buffer!");
        return InvalidAssetID;
    }
    if (size != it->size) {
        freeUniformSpaces.push_back({it->size - size, it->offset + size});
    }

    BufferRegion region{size, it->offset};
    const AssetID id = idSystem->allocate();
    usedUniformSpaces.try_emplace(id, region);

    return id;
}

void VulkanUniformManager::freeUniformBufferRegion(const AssetID id) {
    if (!usedUniformSpaces.contains(id)) {
        LOG_WARNING("failed to free vulkan uniform buffer region, invalid asset id!");
        return;
    }
    coalesceAndFreeBufferRegions(freeUniformSpaces, usedUniformSpaces.at(id));
    usedUniformSpaces.erase(id);
    idSystem->free(id);
}

AssetID VulkanUniformManager::allocateDescriptor(VulkanDescriptorSetLayout &layout) {
    if (availableAllocatableSets < framesInFlight) createPool();
    const AssetID id = idSystem->allocate();
    sets.try_emplace(id, std::make_unique<VulkanUniformDescriptorSets>
        (device, layout, *pools.back(), buffers, framesInFlight, 0, 0));
    return id;
}

void VulkanUniformManager::write(AssetID id, size_t size, void *data) {

}

void VulkanUniformManager::write(const AssetID id, const uint32_t frameIndex, const size_t size, const void *data) {
    if (!usedUniformSpaces.contains(id)) {
        LOG_WARNING("");
        return;
    }
    const auto region = usedUniformSpaces.at(id);
    if (size > region.size) {
        LOG_WARNING("");
        return;
    }
    if (frameIndex >= buffers.size()) {
        LOG_WARNING("");
        return;
    }
    buffers[frameIndex]->write(data, size, region.offset);
}

void VulkanUniformManager::createUniformBuffers(const uint32_t bufferSize) {
    for (uint32_t i = 0; i < framesInFlight; i++) {
        buffers.push_back(device.createVulkanBuffer(bufferSize, BufferType::UniformBuffer));
    }
}

void VulkanUniformManager::createPool() {
    availableAllocatableSets = maxAvailableDescriptorSets;
    pools.push_back(std::make_unique<VulkanUniformDescriptorPool>(device, framesInFlight * maxAvailableDescriptorSets));
}

// === shader cache ===
VulkanCache::VulkanCache(VulkanDevice &device, VulkanSwapChain& swapChain, const uint32_t framesInFlight) {
    idSystem = std::make_unique<IDSystem<AssetID>>();

    pipelineCache = std::make_unique<VulkanPipelineCache>(device, swapChain, idSystem.get());
    bindlessManager = std::make_unique<VulkanBindlessManager>(device, idSystem.get(), maxBindlessTextures, maxBindlessSamplers);
    uniformManager = std::make_unique<VulkanUniformManager>(device, idSystem.get(),
        uniformBufferSize, framesInFlight, maxAvailableUniformDescriptorSets);
}

AssetID VulkanCache::createEntry(const uint32_t propertiesSize, const std::vector<Texture>& textures,
    std::vector<char> code) {
    VulkanCacheEntry entry;

    entry.uniformRegion = uniformManager->allocateUniformBufferRegion(propertiesSize);
    entry.uniformDescriptor = uniformManager->allocateDescriptor(pipelineCache->getTexturePipelineLayout());

    for (const Texture& texture : textures) {
        entry.samplers.push_back(bindlessManager->allocateSampler(texture.getSamplerState()));
        entry.textures.push_back(bindlessManager->allocateTexture(*static_cast<VulkanTexture*>(texture.getNativeHandle()), texture.getHash()));
    }
    entry.pipeline = pipelineCache->allocatePipeline(std::move(code), true);

    const AssetID id = idSystem->allocate();
    entries.try_emplace(id, entry);
    return id;
}

AssetID VulkanCache::createEntry(const uint32_t propertiesSize, std::vector<char> code) {
    VulkanCacheEntry entry{
        .uniformRegion = uniformManager->allocateUniformBufferRegion(propertiesSize),
        .uniformDescriptor = uniformManager->allocateDescriptor(pipelineCache->getUniformPipelineLayout()),
        .pipeline = pipelineCache->allocatePipeline(std::move(code), false)
    };
    const AssetID id = idSystem->allocate();
    entries.try_emplace(id, entry);
    return id;
}

AssetID VulkanCache::createEntry(std::vector<char> code) {
    VulkanCacheEntry entry{
        .pipeline = pipelineCache->allocatePipeline(std::move(code), false)
    };
    const AssetID id = idSystem->allocate();
    entries.try_emplace(id, entry);
    return id;
}

VulkanCacheEntry * VulkanCache::getEntry(const AssetID id) {
    if (!entries.contains(id)) {
        LOG_ERROR("vulkan cache entry id is invalid!");
        return nullptr;
    }
    return &entries.at(id);
}

VulkanAgnosticCache::VulkanAgnosticCache(VulkanDevice &device, VulkanSwapChain &swapChain, uint32_t framesInFlight) {
    cache = std::make_unique<VulkanCache>(device, swapChain, framesInFlight);
}

AssetID VulkanAgnosticCache::createEntry(const AssetID agnosticID, const uint32_t propertiesSize,
    const std::vector<Texture> &textures, std::vector<char> code) {
    const auto id = cache->createEntry(propertiesSize, textures, std::move(code));
    agnosticIDs.try_emplace(agnosticID, id);
    return id;
}

AssetID VulkanAgnosticCache::createEntry(const AssetID agnosticID, const uint32_t propertiesSize, std::vector<char> code) {
    const auto id = cache->createEntry(propertiesSize, std::move(code));
    agnosticIDs.try_emplace(agnosticID, id);
    return id;
}

AssetID VulkanAgnosticCache::createEntry(const AssetID agnosticID, std::vector<char> code) {
    const auto id = cache->createEntry(std::move(code));
    agnosticIDs.try_emplace(agnosticID, id);
    return id;
}

VulkanCacheEntry* VulkanAgnosticCache::getEntry(const AssetID agnosticID) const {
    if (!agnosticIDs.contains(agnosticID)) {
        LOG_ERROR("the material id is invalid, failed to fetch vulkan cache entry!");
        return nullptr;
    }
    return cache->getEntry(agnosticIDs.at(agnosticID));
}
}
