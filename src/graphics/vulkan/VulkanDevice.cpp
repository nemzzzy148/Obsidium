//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "VulkanDevice.h"

namespace obsidium::vulkan {

VulkanDevice::VulkanDevice(VulkanContext& context, VulkanSurface& surface) : context(context) {
    createPhysicalDevice();
    createDevice(surface);
}

// --- physical device ---
bool VulkanDevice::isDeviceSuitable(vk::raii::PhysicalDevice const &physicalDevice, std::vector<char const *> &requiredDeviceExtensions) {
        bool supportsVK13 = physicalDevice.getProperties().apiVersion >= vk::ApiVersion13;

        auto queueFamilies = physicalDevice.getQueueFamilyProperties();
        auto supportsGraphics = std::ranges::any_of(queueFamilies, [](auto const & qfp){ return !!(qfp.queueFlags & vk::QueueFlagBits::eGraphics); });

        auto availableExtensions = physicalDevice.enumerateDeviceExtensionProperties();
        bool supportsAllReqExt = std::ranges::all_of(requiredDeviceExtensions, [&availableExtensions](auto const & reqDevExt) {
            return std::ranges::any_of(availableExtensions, [reqDevExt](auto const & availableDevExt) {
                return strcmp(reqDevExt, availableDevExt.extensionName) == 0;
            });
        });

        auto features = physicalDevice.template getFeatures2<vk::PhysicalDeviceFeatures2,
            vk::PhysicalDeviceVulkan11Features, vk::PhysicalDeviceVulkan13Features,
            vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>();

        auto supportsReqFeatures = features.template get<vk::PhysicalDeviceFeatures2>().features.samplerAnisotropy &&
            features.template get<vk::PhysicalDeviceVulkan11Features>().shaderDrawParameters &&
                features.template get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering &&
                    features.template get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>().extendedDynamicState;

        return supportsVK13 && supportsReqFeatures && supportsAllReqExt && supportsGraphics;
}

void VulkanDevice::createPhysicalDevice() {
    std::vector<vk::raii::PhysicalDevice> physicalDevices = context.getInstance().enumeratePhysicalDevices();

    auto const it = std::ranges::find_if(physicalDevices, [&](auto const & pD) {
        return isDeviceSuitable(pD, requiredDeviceExtensions);
    });

    if (it == physicalDevices.end()) {
        throw std::runtime_error("failed to select physical device");
    }

    physicalDevice = *it;
}

uint32_t VulkanDevice::getQueueIndex(vk::QueueFlagBits flags, const vk::raii::PhysicalDevice &physicalDevice) {
    std::vector<vk::QueueFamilyProperties> queueFamilyProperties = physicalDevice.getQueueFamilyProperties();

    uint32_t queueIndex = ~0;
    for (uint32_t i = 0; i < queueFamilyProperties.size(); i++) {
        if (queueFamilyProperties[i].queueFlags & flags) {
            queueIndex = i;
        }
    }
    return queueIndex;
}

// --- logical device ---
void VulkanDevice::createDevice(VulkanSurface& surface) {
    std::vector<vk::QueueFamilyProperties> queueFamilyProperties = physicalDevice.getQueueFamilyProperties();

    auto gQI = getQueueIndex(vk::QueueFlagBits::eGraphics, physicalDevice);
    graphicsFamily = physicalDevice.getSurfaceSupportKHR(gQI, surface.getHandle()) ? gQI : ~0;

    if (graphicsFamily == ~0) {
        throw std::runtime_error("failed to find a queue that supports graphics!");
    }

    vk::StructureChain<vk::PhysicalDeviceFeatures2,
        vk::PhysicalDeviceVulkan11Features,
        vk::PhysicalDeviceVulkan13Features,
        vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>
    featureChain = {
        {.features = {.samplerAnisotropy = true } },
        {.shaderDrawParameters = true},
        {.synchronization2 = true, .dynamicRendering = true},
        {.extendedDynamicState = true}
    };

    float queuePriority = 0.5;
    vk::DeviceQueueCreateInfo queueInfo{
        .queueFamilyIndex = graphicsFamily,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority
    };

    vk::DeviceCreateInfo deviceCreateInfo{
        .pNext = &featureChain.get<vk::PhysicalDeviceFeatures2>(),
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueInfo,
        .enabledExtensionCount = static_cast<uint32_t>(requiredDeviceExtensions.size()),
        .ppEnabledExtensionNames = requiredDeviceExtensions.data()
    };
    device = vk::raii::Device(physicalDevice, deviceCreateInfo);
    graphicsQueue = vk::raii::Queue(device, graphicsFamily, 0);
}

}
