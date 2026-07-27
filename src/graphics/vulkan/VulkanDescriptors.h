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
    VulkanDescriptorPool(VulkanDevice& device, uint32_t framesInFlight, uint32_t maxSamplers, uint32_t maxTextures);
    vk::raii::DescriptorPool& getUniformPool() { return uniformPool; }
    vk::raii::DescriptorPool& getBindlessPool() { return bindlessPool; }
private:
    void createUniformPool(VulkanDevice &device, uint32_t count);
    vk::raii::DescriptorPool uniformPool = nullptr;
    static constexpr uint32_t bindlessSetCount = 2;
    void createBindlessPool(VulkanDevice &device, uint32_t maxSamplers, uint32_t maxTextures);
    vk::raii::DescriptorPool bindlessPool = nullptr;
};

class VulkanDescriptorSets {
public:
    VulkanDescriptorSets(VulkanDevice &device, VulkanDescriptorSetLayout& descriptorSetLayout,
        VulkanDescriptorPool &descriptorPool, const std::vector<std::unique_ptr<VulkanBuffer>>& uniformBuffers,
        uint32_t framesInFlight, uint32_t maxSamplers, uint32_t maxTextures);

    std::vector<vk::raii::DescriptorSet>& getUniformSet() { return uniformSet; }
    vk::raii::DescriptorSet& getSamplerSet() { return samplerSet; }
    vk::raii::DescriptorSet& getTextureSet() { return textureSet; }
private:
    void createUniformSets(VulkanDevice &device, VulkanDescriptorSetLayout& descriptorSetLayout,
        VulkanDescriptorPool &descriptorPool,
        const std::vector<std::unique_ptr<VulkanBuffer>>& uniformBuffers, uint32_t framesInFlight);
    std::vector<vk::raii::DescriptorSet> uniformSet;

    void createBindlessSet(VulkanDevice &device, VulkanDescriptorSetLayout& descriptorSetLayout,
        VulkanDescriptorPool &descriptorPool, uint32_t maxSamplers, uint32_t maxTextures);
    vk::raii::DescriptorSet samplerSet = nullptr;
    vk::raii::DescriptorSet textureSet = nullptr;
};

}
