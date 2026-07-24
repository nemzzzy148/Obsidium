//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once

#include "VulkanContext.h"

#include "VulkanSurface.h"
#include <glfw/glfw3.h>

#include "../../../include/window/Window.h"

namespace obsidium {
class Window;
}

namespace obsidium::vulkan {

class VulkanSurface {
public:
    VulkanSurface(VulkanContext& context, Window* window) : context(context) {
        // extend later for other WSI
        VkSurfaceKHR _surface;
        VkResult result = VK_ERROR_UNKNOWN;

        switch (window->getBackend()) {
            case WindowBackend::GLFW:
                GLFWwindow* glfwWindow = static_cast<GLFWwindow *>(window->getNativeWindowHandle());
                result = glfwCreateWindowSurface(*context.getInstance(), glfwWindow, nullptr, &_surface);
        }

        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface");
        }

        surface = vk::raii::SurfaceKHR(context.getInstance(), _surface);
    }

    vk::raii::SurfaceKHR& getHandle() { return surface; }
private:
    VulkanContext& context;
    vk::raii::SurfaceKHR surface = nullptr;
};

}
