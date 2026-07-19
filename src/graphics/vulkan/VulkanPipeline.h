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
    VulkanDescriptorSetLayout(VulkanDevice& device);
    vk::raii::DescriptorSetLayout& getHandle() { return descriptorSetLayout; }
private:
    vk::raii::DescriptorSetLayout descriptorSetLayout = nullptr;
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

}
