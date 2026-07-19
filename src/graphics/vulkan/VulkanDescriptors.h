//
// Created by Nemesis Verstraete on 18/07/2026.
//


#pragma once
#include <vulkan/vulkan_raii.hpp>

#include "VulkanBuffer.h"
#include "VulkanDevice.h"
#include "VulkanPipeline.h"

namespace obsidium::vulkan {

class VulkanDescriptorPool {
public:
    VulkanDescriptorPool(VulkanDevice& device, uint32_t maxSets);
    vk::raii::DescriptorPool& getHandle() { return descriptorPool; }
private:
    vk::raii::DescriptorPool descriptorPool = nullptr;
};

class VulkanDescriptorSets {
public:
    VulkanDescriptorSets(VulkanDevice &device, VulkanDescriptorSetLayout& descriptorSetLayout, VulkanDescriptorPool &descriptorPool, std::vector<std::unique_ptr<VulkanBuffer>>& uniformBuffers, uint32_t descriptorCount);
    std::vector<vk::raii::DescriptorSet>& getHandle() { return descriptorSets; }
private:
    std::vector<vk::raii::DescriptorSet> descriptorSets;
};

}
