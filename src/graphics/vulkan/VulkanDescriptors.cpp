//
// Created by Nemesis Verstraete on 18/07/2026.
//

#include "VulkanDescriptors.h"

#include "VulkanBuffer.h"
#include "VulkanPipeline.h"

namespace obsidium::vulkan {

VulkanUniformDescriptorPool::VulkanUniformDescriptorPool(VulkanDevice &device, const uint32_t framesInFlight) {
    createUniformPool(device, framesInFlight);
}

void VulkanUniformDescriptorPool::createUniformPool(VulkanDevice &device, const uint32_t count) {
    const vk::DescriptorPoolSize poolSize{
        .type = vk::DescriptorType::eUniformBuffer,
        .descriptorCount = count
    };
    const vk::DescriptorPoolCreateInfo poolInfo{
        .flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet,
        .maxSets = count,
        .poolSizeCount = 1,
        .pPoolSizes = &poolSize
    };
    pool = vk::raii::DescriptorPool(device.getDevice(), poolInfo);
}

VulkanBindlessDescriptorPool::VulkanBindlessDescriptorPool(VulkanDevice &device, const uint32_t maxSamplers, const uint32_t maxTextures) {
    createBindlessPool(device, maxSamplers, maxTextures);
}

void VulkanBindlessDescriptorPool::createBindlessPool(VulkanDevice &device, const uint32_t maxSamplers, const uint32_t maxTextures) {
    const std::array<vk::DescriptorPoolSize, 2> poolSizes{{
        {
            .type = vk::DescriptorType::eSampler,
            .descriptorCount = maxSamplers
        },{
            .type = vk::DescriptorType::eSampledImage,
            .descriptorCount = maxTextures
        }}};
    const vk::DescriptorPoolCreateInfo poolInfo{
        .flags = vk::DescriptorPoolCreateFlagBits::eUpdateAfterBind,
        .maxSets = bindlessSetCount,
        .poolSizeCount = static_cast<uint32_t>(poolSizes.size()),
        .pPoolSizes = poolSizes.data()
    };
    bindlessPool = vk::raii::DescriptorPool(device.getDevice(), poolInfo);
}

VulkanUniformDescriptorSets::VulkanUniformDescriptorSets(VulkanDevice &device,
    VulkanDescriptorSetLayout &descriptorSetLayout, VulkanUniformDescriptorPool &uniformPool,
    const std::vector<std::unique_ptr<VulkanBuffer>> &uniformBuffers, const uint32_t framesInFlight, const uint32_t size,
    const uint32_t offset) {
    createUniformSets(device, descriptorSetLayout, uniformPool, uniformBuffers, framesInFlight, size, offset);
}

void VulkanUniformDescriptorSets::createUniformSets(VulkanDevice &device,
    VulkanDescriptorSetLayout &descriptorSetLayout, VulkanUniformDescriptorPool &uniformPool,
    const std::vector<std::unique_ptr<VulkanBuffer>> &uniformBuffers, const uint32_t count, const uint32_t size,
    const uint32_t offset) {
    const std::vector layouts(count, *descriptorSetLayout.getUnformSetLayout());
    const vk::DescriptorSetAllocateInfo allocInfo{
        .descriptorPool = *uniformPool.getHandle(),
        .descriptorSetCount = count,
        .pSetLayouts = layouts.data()
    };
    uniformSet = device.getDevice().allocateDescriptorSets(allocInfo);

    for (size_t i = 0; i < count; i++) {
        vk::DescriptorBufferInfo bufferInfo{
            .buffer = uniformBuffers[i]->getBuffer(),
            .offset = offset,
            .range = size
        };

        vk::WriteDescriptorSet descriptorWrite{
            .dstSet = uniformSet[i],
            .dstBinding = 0,
            .dstArrayElement = 0,
            .descriptorCount = 1,
            .descriptorType = vk::DescriptorType::eUniformBufferDynamic,
            .pBufferInfo = &bufferInfo
        };

        device.getDevice().updateDescriptorSets(descriptorWrite, {});
    }
}

VulkanBindlessDescriptorSets::VulkanBindlessDescriptorSets(VulkanDevice &device, VulkanDescriptorSetLayout &descriptorSetLayout,
        VulkanBindlessDescriptorPool &bindlessPool, const uint32_t maxSamplers, const uint32_t maxTextures) : device(device) {
    createBindlessSet(descriptorSetLayout, bindlessPool, maxSamplers, maxTextures);
}

void VulkanBindlessDescriptorSets::updateTextureSet(const vk::raii::ImageView &view, const uint32_t index) const {
    const vk::DescriptorImageInfo imageInfo{
        .imageView = view,
        .imageLayout = vk::ImageLayout::eShaderReadOnlyOptimal
    };
    const vk::WriteDescriptorSet write{
        .dstSet = *textureSet,
        .dstBinding = 2,
        .dstArrayElement = index,
        .descriptorCount = 1,
        .descriptorType = vk::DescriptorType::eSampledImage,
        .pImageInfo = &imageInfo
    };
    device.getDevice().updateDescriptorSets(write, nullptr);
}

void VulkanBindlessDescriptorSets::updateSamplerSet(const vk::raii::Sampler &sampler, uint32_t index) const {
    const vk::DescriptorImageInfo samplerInfo{
        .sampler = sampler
    };
    const vk::WriteDescriptorSet write{
        .dstSet = *samplerSet,
        .dstBinding = 1,
        .descriptorCount = 1,
        .descriptorType = vk::DescriptorType::eSampler,
        .pImageInfo = &samplerInfo
    };
    device.getDevice().updateDescriptorSets(write, nullptr);
}

void VulkanBindlessDescriptorSets::createBindlessSet(VulkanDescriptorSetLayout &descriptorSetLayout,
                                                     VulkanBindlessDescriptorPool &bindlessPool, const uint32_t maxSamplers, const uint32_t maxTextures) {

    std::array layouts{ *descriptorSetLayout.getSamplerSetLayout(), *descriptorSetLayout.getTextureSetLayout() };

    std::array variableCount{maxSamplers, maxTextures};
    const vk::DescriptorSetVariableDescriptorCountAllocateInfo variableInfo{
        .descriptorSetCount = static_cast<uint32_t>(variableCount.size()),
        .pDescriptorCounts = variableCount.data()
    };
    const vk::DescriptorSetAllocateInfo allocInfo{
        .pNext = &variableInfo,
        .descriptorPool = *bindlessPool.getHandle(),
        .descriptorSetCount = static_cast<uint32_t>(layouts.size()),
        .pSetLayouts =  layouts.data()
    };
    auto sets = device.getDevice().allocateDescriptorSets( allocInfo );

    samplerSet = std::move( sets[0] );
    textureSet = std::move( sets[1] );
}

}