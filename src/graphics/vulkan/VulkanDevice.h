//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "VulkanContext.h"
#include "VulkanSurface.h"

namespace obsidium::vulkan {

class VulkanDevice {
public:
    VulkanDevice(VulkanContext& context, VulkanSurface& surface);

    vk::raii::PhysicalDevice& getPhysicalDevice() { return physicalDevice; }
    vk::raii::Device& getDevice() { return device; }
    vk::Queue getGraphicsQueue() { return  graphicsQueue; }
    uint32_t getGraphicsFamily() const { return  graphicsFamily; }
private:
    VulkanContext& context;
    // physicalDevice
    std::vector<const char*> requiredDeviceExtensions = {vk::KHRSwapchainExtensionName};
    vk::raii::PhysicalDevice physicalDevice = nullptr;

    static bool isDeviceSuitable(vk::raii::PhysicalDevice const & physicalDevice,
        std::vector<const char*>& requiredDeviceExtensions);
    void createPhysicalDevice();

    // logical device
    vk::raii::Device device = nullptr;

    static uint32_t getQueueIndex(vk::QueueFlagBits flags, const vk::raii::PhysicalDevice& physicalDevice);
    void createDevice(VulkanSurface& surface);

    // graphics queue
    uint32_t graphicsFamily = 0;
    vk::raii::Queue graphicsQueue = nullptr;
};

}
