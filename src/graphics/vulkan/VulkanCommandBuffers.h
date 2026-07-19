//
// Created by Nemesis Verstraete on 17/07/2026.
//

#pragma once
#include "VulkanCommandPool.h"
#include "VulkanDevice.h"
#include <vulkan/vulkan_raii.hpp>

namespace obsidium::vulkan {

class VulkanCommandBuffers {
public:
    VulkanCommandBuffers(VulkanDevice& device, VulkanCommandPool& commandPool, uint32_t amount);

    vk::raii::CommandBuffer& getHandle(uint32_t index) { return commandBuffers[index]; }
    std::vector<vk::raii::CommandBuffer>& getHandle() { return commandBuffers; }
private:
    std::vector<vk::raii::CommandBuffer> commandBuffers;
};

}
