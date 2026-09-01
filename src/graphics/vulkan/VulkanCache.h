//
// Created by Nemesis Verstraete on 29/07/2026.
//
#pragma once
#include <memory>
#include <vector>

#include "VulkanDescriptors.h"
#include "VulkanTexture.h"
#include "../../utils/IDSystem.h"
#include "../../../include/graphics/Texture.h"

namespace obsidium::vulkan {
class VulkanTexture;
class VulkanUniformDescriptorPool;
class VulkanPipeline;

struct VulkanLayoutConfiguration {
    std::unique_ptr<VulkanDescriptorSetLayout> descriptorSetLayout;
    std::unique_ptr<VulkanPipelineLayout> pipelineLayout;
};

class VulkanPipelineCache {
public:
    VulkanPipelineCache(VulkanDevice& device, VulkanSwapChain& swapChain, IDSystem<AssetID>* idSystem);
    VulkanPipeline& getPipeline(AssetID id) const;

    [[nodiscard]] VulkanDescriptorSetLayout& getUniformPipelineLayout() const { return *uniformSetLayout.descriptorSetLayout; }
    [[nodiscard]] VulkanDescriptorSetLayout& getTexturePipelineLayout() const { return *textureSetLayout.descriptorSetLayout; }

    AssetID allocatePipeline(std::vector<char> code, bool requiresTextures);
    void destroyPipeline(AssetID id);
private:
    VulkanDevice& device;
    IDSystem<AssetID>* idSystem = nullptr;

    // default render target is swap chain
    VulkanSwapChain& swapChain;

    VulkanLayoutConfiguration uniformSetLayout;
    VulkanLayoutConfiguration textureSetLayout;

    std::unordered_map<AssetID, std::unique_ptr<VulkanPipeline>> pipelines;
    std::unordered_map<uint64_t, AssetID> hashes;
};

class VulkanBindlessManager {
public:
    VulkanBindlessManager(VulkanDevice& device, IDSystem<AssetID>* idSystem, uint32_t maxTextures, uint32_t maxSamplers);

    AssetID allocateTexture(VulkanTexture& texture, uint64_t hash);
    void destroyTexture(AssetID id);

    AssetID allocateSampler(SamplerState state);
    void destroySampler(AssetID id);
private:
    VulkanDevice& device;

    IDSystem<AssetID>* idSystem = nullptr;

    // textures
    uint32_t maxTextures;
    std::vector<uint32_t> freeTextureIndices;
    std::unordered_map<AssetID, uint32_t> textureIndices;
    std::unordered_map<uint64_t, AssetID> textureHashes;

    // samplers
    uint32_t maxSamplers;
    std::vector<uint32_t> freeSamplerIndices;
    std::unordered_map<AssetID, uint32_t> samplerIndices;
    std::unordered_map<AssetID, std::unique_ptr<VulkanSampler>> samplers;
    std::unordered_map<SamplerState, AssetID> samplerStates;

    std::unique_ptr<VulkanBindlessDescriptorPool> pool;
    std::unique_ptr<VulkanBindlessDescriptorSets> sets;
};

class VulkanUniformManager {
public:
    VulkanUniformManager(VulkanDevice& device, IDSystem<AssetID>* idSystem, uint32_t bufferSize,
        uint32_t framesInFlight, uint32_t maxAvailableDescriptorSets);

    AssetID allocateUniformBufferRegion(uint32_t size);
    void freeUniformBufferRegion(AssetID id);

    AssetID allocateDescriptor(VulkanDescriptorSetLayout& layout);

    void write(AssetID id, size_t size, void* data);
    void write(AssetID id, uint32_t frameIndex, size_t size, const void* data);
private:
    VulkanDevice& device;
    IDSystem<AssetID>* idSystem = nullptr;

    // buffer
    uint32_t framesInFlight;
    void createUniformBuffers(uint32_t bufferSize);
    std::vector<std::unique_ptr<VulkanBuffer>> buffers;

    uint32_t byteAlignment;
    std::vector<BufferRegion> freeUniformSpaces;
    std::unordered_map<AssetID, BufferRegion> usedUniformSpaces;

    // descriptors
    uint32_t maxAvailableDescriptorSets;
    uint32_t availableAllocatableSets;
    void createPool();
    std::vector<std::unique_ptr<VulkanUniformDescriptorPool>> pools;
    std::unordered_map<AssetID, std::unique_ptr<VulkanUniformDescriptorSets>> sets;
};

struct VulkanCacheEntry {
    std::vector<AssetID> textures; // linked to higher abstraction, api agnostic texture manager
    std::vector<AssetID> samplers;
    AssetID uniformRegion = InvalidAssetID;
    AssetID uniformDescriptor = InvalidAssetID;
    AssetID pipeline; // required
};

class VulkanCache {
public:
    explicit VulkanCache(VulkanDevice& device, VulkanSwapChain& swapChain, uint32_t framesInFlight);

    AssetID createEntry(uint32_t propertiesSize, const std::vector<Texture>& textures, std::vector<char> code);
    AssetID createEntry(uint32_t propertiesSize, std::vector<char> code);
    AssetID createEntry(std::vector<char> code);

    VulkanCacheEntry* getEntry(AssetID id);
private:
    std::unique_ptr<IDSystem<AssetID>> idSystem;

    // shader cache
    std::unordered_map<AssetID, VulkanCacheEntry> entries;

    // specific cache config
    std::unique_ptr<VulkanPipelineCache> pipelineCache;

    static constexpr uint32_t maxBindlessTextures = 4096;
    static constexpr uint32_t maxBindlessSamplers = 32;
    std::unique_ptr<VulkanBindlessManager> bindlessManager;

    static constexpr uint32_t uniformBufferSize = 131072; // 128 KB
    static constexpr uint32_t maxAvailableUniformDescriptorSets = 128; // per pool
    std::unique_ptr<VulkanUniformManager> uniformManager;
};

class VulkanAgnosticCache {
public:
    explicit VulkanAgnosticCache(VulkanDevice& device, VulkanSwapChain& swapChain, uint32_t framesInFlight);

    AssetID createEntry(AssetID agnosticID, uint32_t propertiesSize,
        const std::vector<Texture>& textures, std::vector<char> code);
    AssetID createEntry(AssetID agnosticID, uint32_t propertiesSize, std::vector<char> code);
    AssetID createEntry(AssetID agnosticID, std::vector<char> code);

    VulkanCacheEntry* getEntry(AssetID agnosticID) const;
private:
    std::unordered_map<AssetID, AssetID> agnosticIDs;

    std::unique_ptr<VulkanCache> cache;
};

}