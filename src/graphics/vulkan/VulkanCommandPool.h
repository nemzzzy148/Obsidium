//
// Created by Nemesis Verstraete on 17/07/2026.
//

#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "VulkanDevice.h"

namespace obsidium::vulkan {

class VulkanCommandPool {
public:
    VulkanCommandPool(VulkanDevice& device, uint32_t familyIndex);

    vk::raii::CommandPool& getHandle() { return commandPool; }
private:
    uint32_t familyIndex;
    vk::raii::CommandPool commandPool = nullptr;
};

}
