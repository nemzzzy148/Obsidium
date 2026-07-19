//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

#include "vulkan/vulkan_raii.hpp"

namespace obsidium::vulkan {

class VulkanContext {
public:
    VulkanContext(std::vector<char const*> requiredExtensions);
    ~VulkanContext() = default;

    vk::raii::Context& getContext() { return context; }
    vk::raii::Instance& getInstance() { return instance; }
private:
    vk::raii::Context context;

    // instance
    vk::raii::Instance instance = nullptr;
    void createInstance(std::vector<char const*> requiredExtensions);

    // validation layers & debugger
    const std::vector<char const*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    vk::raii::DebugUtilsMessengerEXT debugMessenger = nullptr;

    void setupDebugMessenger();
};

}
