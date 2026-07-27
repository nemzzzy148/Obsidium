//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include "VulkanDevice.h"

namespace obsidium::vulkan {

class VulkanSwapChain {
public:
    VulkanSwapChain(VulkanDevice& device, VulkanSurface& surface, uint32_t width, uint32_t height);

    void recreate(uint32_t width, uint32_t height);

    vk::raii::SwapchainKHR& getHandle() { return *swapChain; }
    vk::SurfaceFormatKHR& getFormat() { return format; }
    std::vector<vk::Image>& getImages() { return images; }
    std::vector<vk::raii::ImageView>& getImageViews() { return imageViews; }
    [[nodiscard]] vk::Extent2D getExtent() const { return extent; }
    std::vector<vk::raii::Semaphore>& getPresentCompleteSemaphores() { return presentCompleteSemaphores; };

    uint32_t imageIndex = 0;
private:
    VulkanDevice& device;
    VulkanSurface& surface;

    std::optional<vk::raii::SwapchainKHR> swapChain;
    std::vector<vk::Image> images;
    vk::Extent2D extent;
    vk::SurfaceFormatKHR format;
    std::vector<vk::raii::ImageView> imageViews;
    std::vector<vk::raii::Semaphore> presentCompleteSemaphores;

    static vk::Extent2D chooseExtent(vk::SurfaceCapabilitiesKHR const &capabilities, uint32_t width, uint32_t height);
    static vk::SurfaceFormatKHR chooseFormat(std::vector<vk::SurfaceFormatKHR> const &availableFormats);
    static uint32_t chooseMinImageCount(vk::SurfaceCapabilitiesKHR const &capabilities);
    static vk::PresentModeKHR chooseSwapPresentMode(std::vector<vk::PresentModeKHR> const &availablePresentModes);

    void createSwapChain(uint32_t width, uint32_t height);
};


}
