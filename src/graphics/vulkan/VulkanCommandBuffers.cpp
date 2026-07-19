//
// Created by Nemesis Verstraete on 17/07/2026.
//

#include "VulkanCommandBuffers.h"

namespace obsidium::vulkan {

VulkanCommandBuffers::VulkanCommandBuffers(VulkanDevice &device, VulkanCommandPool &commandPool, uint32_t amount) {
    vk::CommandBufferAllocateInfo allocInfo{
        .commandPool = commandPool.getHandle(),
        .level = vk::CommandBufferLevel::ePrimary,
        .commandBufferCount = amount
    };

    commandBuffers = vk::raii::CommandBuffers(device.getDevice(), allocInfo);
}

}
