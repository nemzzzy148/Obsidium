//
// Created by Nemesis Verstraete on 30/08/2026.
//

#pragma once
#include <vulkan/vulkan_raii.hpp>

namespace rhi::vulkan {
class VulkanDevice;

class VulkanQueue {
public:
    explicit VulkanQueue(const VulkanDevice& device);
private:
    vk::raii::Queue queue = nullptr;
};

}
