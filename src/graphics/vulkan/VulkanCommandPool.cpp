//
// Created by Nemesis Verstraete on 17/07/2026.
//

#include "VulkanCommandPool.h"

namespace obsidium::vulkan {

VulkanCommandPool::VulkanCommandPool(VulkanDevice &device, uint32_t familyIndex) : familyIndex(familyIndex) {
    vk::CommandPoolCreateInfo poolInfo{
        .flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
        .queueFamilyIndex = familyIndex
    };
    commandPool = vk::raii::CommandPool(device.getDevice(), poolInfo);
}

}
