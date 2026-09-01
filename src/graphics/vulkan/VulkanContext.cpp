//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "VulkanContext.h"

#include <iostream>

VulkanContext::VulkanContext(std::vector<char const*> requiredExtensions) {
    createInstance(std::move(requiredExtensions));
    setupDebugMessenger();
}

// --- instance ---
void VulkanContext::createInstance(std::vector<char const*> requiredExtensions) {
    vk::ApplicationInfo appInfo{
        .pApplicationName = "obsidium_runtime",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "obsidium",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = vk::ApiVersion14
    };

    std::vector<char const*> requiredLayers;
    if (enableValidationLayers) {
        requiredLayers.assign(validationLayers.begin(), validationLayers.end());
    }
    auto layerProps = context.enumerateInstanceLayerProperties();
    if (std::ranges::any_of(requiredLayers, [&layerProps](auto const& requiredLayer) {
        return std::ranges::none_of(layerProps, [requiredLayer](auto const& layerProp) {
            return strcmp(requiredLayer, layerProp.layerName) == 0;
        });
    })) {
        throw std::runtime_error("one or more layers not available!");
    }

    if (enableValidationLayers) {
        requiredExtensions.push_back(vk::EXTDebugUtilsExtensionName);
    }

    auto extensionProps = context.enumerateInstanceExtensionProperties();

    auto unsupportedPropIt = std::ranges::find_if(requiredExtensions, [&extensionProps](auto const& requiredExt) {
        return std::ranges::none_of(extensionProps, [requiredExt](auto const &extProp) {
            return strcmp(requiredExt, extProp.extensionName) == 0;
        });
    });

    if (unsupportedPropIt != requiredExtensions.end()) {
        throw std::runtime_error("required extension not supported: " + std::string(*unsupportedPropIt));
    }

    vk::InstanceCreateInfo createInfo{
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = static_cast<uint32_t>(requiredLayers.size()),
        .ppEnabledLayerNames = requiredLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size()),
        .ppEnabledExtensionNames = requiredExtensions.data()
    };

    instance = vk::raii::Instance(context, createInfo);
}

// --- debug messenger ---
VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
              vk::DebugUtilsMessageTypeFlagsEXT type,
              const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData,
              void *userData) {
    std::cerr << "validation layer: type" + vk::to_string(type) << " message: " << pCallbackData->pMessage << std::endl;
    return vk::False;
}

void VulkanContext::setupDebugMessenger() {
    if (!enableValidationLayers) return;
    vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);
    vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
        vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);

    vk::DebugUtilsMessengerCreateInfoEXT messengerCreateInfo{
        .messageSeverity = severityFlags,
        .messageType = messageTypeFlags,
        .pfnUserCallback = &debugCallback
    };

    debugMessenger = instance.createDebugUtilsMessengerEXT( messengerCreateInfo );
}