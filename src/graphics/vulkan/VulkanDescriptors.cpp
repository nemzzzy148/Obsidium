//
// Created by Nemesis Verstraete on 18/07/2026.
//

#include "VulkanDescriptors.h"

#include "VulkanBuffer.h"
#include "VulkanPipeline.h"

namespace obsidium::vulkan {

VulkanDescriptorPool::VulkanDescriptorPool(VulkanDevice &device, uint32_t maxSets) {
    std::array<vk::DescriptorPoolSize, 1> poolSizes{{
            {
                .type = vk::DescriptorType::eUniformBuffer,
                .descriptorCount = maxSets
            }
    }};
    vk::DescriptorPoolCreateInfo poolInfo{
        .flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet,
        .maxSets = maxSets,
        .poolSizeCount = static_cast<uint32_t>(poolSizes.size()),
        .pPoolSizes = poolSizes.data()
    };
    descriptorPool = vk::raii::DescriptorPool(device.getDevice(), poolInfo);
}

VulkanDescriptorSets::VulkanDescriptorSets(VulkanDevice &device, VulkanDescriptorSetLayout& descriptorSetLayout, VulkanDescriptorPool &descriptorPool, std::vector<std::unique_ptr<VulkanBuffer>>& uniformBuffers, uint32_t descriptorCount) {
    std::vector<vk::DescriptorSetLayout> layouts(descriptorCount, *descriptorSetLayout.getHandle());
    vk::DescriptorSetAllocateInfo allocInfo{
        .descriptorPool = descriptorPool.getHandle(),
        .descriptorSetCount = descriptorCount,
        .pSetLayouts = layouts.data()
    };

    descriptorSets = device.getDevice().allocateDescriptorSets(allocInfo);

    for (size_t i = 0; i < descriptorCount; i++) {
        vk::DescriptorBufferInfo bufferInfo{
            .buffer = uniformBuffers[i]->getBuffer(),
            .offset = 0,
            .range = sizeof(rhi::UniformBufferObject)
        };

        // image func

        std::array<vk::WriteDescriptorSet, 1> descriptorWrites{{
            {
                .dstSet = descriptorSets[i],
                .dstBinding = 0,
                .dstArrayElement = 0,
                .descriptorCount = 1,
                .descriptorType = vk::DescriptorType::eUniformBuffer,
                .pBufferInfo = &bufferInfo
            }
        }};

        device.getDevice().updateDescriptorSets(descriptorWrites, {});
    }
}
}
