//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "VulkanDevice.h"
#include "VulkanSwapChain.h"

namespace obsidium::vulkan {

class VulkanDescriptorSetLayout {
public:
    VulkanDescriptorSetLayout(VulkanDevice& device, uint32_t maxSamplers, uint32_t maxTextures);
    vk::raii::DescriptorSetLayout& getUnformSetLayout() { return uniformSetLayout; }
    vk::raii::DescriptorSetLayout& getSamplerSetLayout() { return samplerSetLayout; }
    vk::raii::DescriptorSetLayout& getTextureSetLayout() { return textureSetLayout; }

    static constexpr vk::DescriptorBindingFlags variableFlags =
        vk::DescriptorBindingFlagBits::ePartiallyBound |
        vk::DescriptorBindingFlagBits::eVariableDescriptorCount |
        vk::DescriptorBindingFlagBits::eUpdateAfterBind;
private:
    void createUniformSetLayout(VulkanDevice& device);
    vk::raii::DescriptorSetLayout uniformSetLayout = nullptr;
    void createSamplerSetLayout(VulkanDevice& device, uint32_t maxSamplers);
    vk::raii::DescriptorSetLayout samplerSetLayout = nullptr;
    void createTextureSetLayout(VulkanDevice& device, uint32_t maxTextures);
    vk::raii::DescriptorSetLayout textureSetLayout = nullptr;
};

class VulkanPipelineLayout {
public:
    VulkanPipelineLayout(VulkanDevice& device, VulkanDescriptorSetLayout& descriptorSetLayout);
    vk::raii::PipelineLayout& getHandle() { return pipelineLayout; }
private:
    vk::raii::PipelineLayout pipelineLayout = nullptr;
};

class VulkanPipeline {
public:
    VulkanPipeline(VulkanDevice &device, VulkanSwapChain& swapChain, VulkanPipelineLayout& pipelineLayout, std::vector<char> code);

    vk::raii::Pipeline& getHandle() { return pipeline; }
private:
    vk::raii::Pipeline pipeline = nullptr;
};

class VulkanPipelineCache {
    VulkanPipelineCache() = default;
    VulkanPipeline& getPipeline(uint32_t index);
private:
    std::vector<VulkanPipeline> pipelines;
};

}
