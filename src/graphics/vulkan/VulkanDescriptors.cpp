//
// Created by Nemesis Verstraete on 18/07/2026.
//

#include "VulkanDescriptors.h"

#include "VulkanBuffer.h"
#include "VulkanPipeline.h"

namespace obsidium::vulkan {

VulkanDescriptorPool::VulkanDescriptorPool(VulkanDevice &device, const uint32_t framesInFlight, const uint32_t maxSamplers, const uint32_t maxTextures) {
    createUniformPool(device, framesInFlight);
    createBindlessPool(device, maxSamplers, maxTextures);
}

void VulkanDescriptorPool::createUniformPool(VulkanDevice &device, const uint32_t count) {
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
    uniformPool = vk::raii::DescriptorPool(device.getDevice(), poolInfo);
}

void VulkanDescriptorPool::createBindlessPool(VulkanDevice &device, const uint32_t maxSamplers, const uint32_t maxTextures) {
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

VulkanDescriptorSets::VulkanDescriptorSets(VulkanDevice &device, VulkanDescriptorSetLayout &descriptorSetLayout,
    VulkanDescriptorPool &descriptorPool, const std::vector<std::unique_ptr<VulkanBuffer>> &uniformBuffers,
    const uint32_t framesInFlight, const uint32_t maxSamplers, const uint32_t maxTextures) {
    createUniformSets(device, descriptorSetLayout, descriptorPool, uniformBuffers, framesInFlight);
    createBindlessSet(device, descriptorSetLayout, descriptorPool, maxSamplers, maxTextures);

}

void VulkanDescriptorSets::createUniformSets(VulkanDevice &device, VulkanDescriptorSetLayout &descriptorSetLayout,
                                             VulkanDescriptorPool &descriptorPool,
                                             const std::vector<std::unique_ptr<VulkanBuffer>> &uniformBuffers,
                                             const uint32_t framesInFlight) {
    std::vector<vk::DescriptorSetLayout> layouts(framesInFlight, *descriptorSetLayout.getUnformSetLayout());
    const vk::DescriptorSetAllocateInfo allocInfo{
        .descriptorPool = *descriptorPool.getUniformPool(),
        .descriptorSetCount = framesInFlight,
        .pSetLayouts = layouts.data()
    };
    uniformSet = device.getDevice().allocateDescriptorSets(allocInfo);

    for (size_t i = 0; i < framesInFlight; i++) {
        vk::DescriptorBufferInfo bufferInfo{
            .buffer = uniformBuffers[i]->getBuffer(),
            .offset = 0,
            .range = sizeof(rhi::UniformBufferObject)
        };

        vk::WriteDescriptorSet descriptorWrite{
            .dstSet = uniformSet[i],
            .dstBinding = 0,
            .dstArrayElement = 0,
            .descriptorCount = 1,
            .descriptorType = vk::DescriptorType::eUniformBuffer,
            .pBufferInfo = &bufferInfo
        };

        device.getDevice().updateDescriptorSets(descriptorWrite, {});
    }
}

void VulkanDescriptorSets::createBindlessSet(VulkanDevice &device, VulkanDescriptorSetLayout &descriptorSetLayout,
    VulkanDescriptorPool &descriptorPool, const uint32_t maxSamplers, const uint32_t maxTextures) {

    std::array<vk::DescriptorSetLayout, 2> layouts{ *descriptorSetLayout.getSamplerSetLayout(), *descriptorSetLayout.getTextureSetLayout() };

    std::array<uint32_t, 2> variableCount{maxSamplers, maxTextures};
    const vk::DescriptorSetVariableDescriptorCountAllocateInfo variableInfo{
        .descriptorSetCount = static_cast<uint32_t>(variableCount.size()),
        .pDescriptorCounts = variableCount.data()
    };
    const vk::DescriptorSetAllocateInfo allocInfo{
        .pNext = &variableInfo,
        .descriptorPool = *descriptorPool.getBindlessPool(),
        .descriptorSetCount = static_cast<uint32_t>(layouts.size()),
        .pSetLayouts =  layouts.data()
    };
    auto sets = device.getDevice().allocateDescriptorSets( allocInfo );

    samplerSet = std::move( sets[0] );
    textureSet = std::move( sets[1] );
}

}

