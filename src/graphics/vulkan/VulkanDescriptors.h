//
// Created by Nemesis Verstraete on 18/07/2026.
//


#pragma once
#include <vulkan/vulkan_raii.hpp>

#include "VulkanBuffer.h"
#include "VulkanDevice.h"
#include "VulkanPipeline.h"

namespace obsidium::vulkan {

class VulkanUniformDescriptorPool {
public:
    VulkanUniformDescriptorPool(VulkanDevice& device, uint32_t framesInFlight);
    vk::raii::DescriptorPool& getHandle() { return pool; }
private:
    void createUniformPool(VulkanDevice &device, uint32_t count);
    vk::raii::DescriptorPool pool = nullptr;
};

class VulkanBindlessDescriptorPool {
public:
    VulkanBindlessDescriptorPool(VulkanDevice& device, uint32_t maxSamplers, uint32_t maxTextures);
    vk::raii::DescriptorPool& getHandle() { return bindlessPool; }
private:
    static constexpr uint32_t bindlessSetCount = 2; // set count != types!
    void createBindlessPool(VulkanDevice &device, uint32_t maxSamplers, uint32_t maxTextures);
    vk::raii::DescriptorPool bindlessPool = nullptr;
};

class VulkanUniformDescriptorSets {
public:
    VulkanUniformDescriptorSets(VulkanDevice &device, VulkanDescriptorSetLayout& descriptorSetLayout,
        VulkanUniformDescriptorPool &uniformPool, const std::vector<std::unique_ptr<VulkanBuffer>>& uniformBuffers,
        uint32_t framesInFlight, uint32_t size, uint32_t offset);
    std::vector<vk::raii::DescriptorSet>& getHandle() { return uniformSet; }
private:
    void createUniformSets(VulkanDevice &device, VulkanDescriptorSetLayout& descriptorSetLayout,
        VulkanUniformDescriptorPool &uniformPool, const std::vector<std::unique_ptr<VulkanBuffer>>& uniformBuffers,
        uint32_t count, uint32_t size, uint32_t offset);
    std::vector<vk::raii::DescriptorSet> uniformSet;
};

class VulkanBindlessDescriptorSets {
public:
    VulkanBindlessDescriptorSets(VulkanDevice &device, VulkanDescriptorSetLayout& descriptorSetLayout,
        VulkanBindlessDescriptorPool &bindlessPool, uint32_t maxSamplers, uint32_t maxTextures);
    vk::raii::DescriptorSet& getSamplerSet() { return samplerSet; }
    vk::raii::DescriptorSet& getTextureSet() { return textureSet; }

    void updateTextureSet(const vk::raii::ImageView& view, uint32_t index) const;
    void updateSamplerSet(const vk::raii::Sampler& sampler, uint32_t index) const;
private:
    void createBindlessSet(VulkanDescriptorSetLayout& descriptorSetLayout,
        VulkanBindlessDescriptorPool &bindlessPool, uint32_t maxSamplers, uint32_t maxTextures);
    VulkanDevice& device;
    vk::raii::DescriptorSet samplerSet = nullptr;
    vk::raii::DescriptorSet textureSet = nullptr;
};

}