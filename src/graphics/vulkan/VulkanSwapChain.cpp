//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "VulkanSwapChain.h"

namespace obsidium::vulkan {

VulkanSwapChain::VulkanSwapChain(VulkanDevice &device, VulkanSurface &surface, uint32_t width, uint32_t height)
    : device(device), surface(surface) {
    createSwapChain(width, height);
}

vk::Extent2D VulkanSwapChain::chooseExtent(vk::SurfaceCapabilitiesKHR const &capabilities, uint32_t width, uint32_t height) {
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    }

    return {
        std::clamp<uint32_t>(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width),
        std::clamp<uint32_t>(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height)
    };
}

vk::SurfaceFormatKHR VulkanSwapChain::chooseFormat(std::vector<vk::SurfaceFormatKHR> const &availableFormats) {
    const auto it = std::ranges::find_if(availableFormats, [](const auto &format) {
        return format.format == vk::Format::eB8G8R8A8Sint && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear;
    });
    return it != availableFormats.end() ? *it : availableFormats[0];
}

uint32_t VulkanSwapChain::chooseMinImageCount(vk::SurfaceCapabilitiesKHR const &capabilities) {
    auto minImageCount = std::max(3u, capabilities.minImageCount);
    if ((0 < capabilities.maxImageCount) && (minImageCount > capabilities.maxImageCount)) {
        minImageCount = capabilities.maxImageCount;
    }
    return minImageCount;
}

vk::PresentModeKHR VulkanSwapChain::chooseSwapPresentMode(std::vector<vk::PresentModeKHR> const &availablePresentModes) {
    return std::ranges::any_of(availablePresentModes, [](const vk::PresentModeKHR present) {
        return vk::PresentModeKHR::eMailbox == present;}) ?
    vk::PresentModeKHR::eMailbox : vk::PresentModeKHR::eFifo;
}

void VulkanSwapChain::createSwapChain(uint32_t width, uint32_t height) {
    auto surfaceCapabilities = device.getPhysicalDevice().getSurfaceCapabilitiesKHR(surface.getHandle());
    extent = chooseExtent(surfaceCapabilities, width, height);

    std::vector<vk::SurfaceFormatKHR> availableFormats = device.getPhysicalDevice().getSurfaceFormatsKHR(surface.getHandle());
    format = chooseFormat(availableFormats);

    uint32_t minImageCount = chooseMinImageCount(surfaceCapabilities);

    std::vector<vk::PresentModeKHR> availablePresentMode = device.getPhysicalDevice().getSurfacePresentModesKHR(surface.getHandle());
    vk::PresentModeKHR presentMode = chooseSwapPresentMode(availablePresentMode);

    vk::SwapchainCreateInfoKHR swapCreateInfo{
        .surface = surface.getHandle(),
        .minImageCount = minImageCount,
        .imageFormat = format.format,
        .imageColorSpace = format.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
        .imageSharingMode = vk::SharingMode::eExclusive,
        .preTransform = surfaceCapabilities.currentTransform,
        .compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque,
        .presentMode = presentMode,
        .clipped = true,
        .oldSwapchain = nullptr
    };

    images.clear();
    imageViews.clear();

    swapChain = vk::raii::SwapchainKHR(device.getDevice(), swapCreateInfo);
    images = swapChain->getImages();

    vk::ImageViewCreateInfo viewCreateInfo{
        .viewType = vk::ImageViewType::e2D,
        .format = format.format,
        .subresourceRange = {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}
    };
    for (const auto &image : images) {
        viewCreateInfo.image = image;
        imageViews.emplace_back(device.getDevice(), viewCreateInfo);
    }

    for (uint32_t i = 0; i < images.size(); i++) {
        presentCompleteSemaphores.emplace_back(device.getDevice(), vk::SemaphoreCreateInfo());
    }
}

void VulkanSwapChain::recreate(uint32_t width, uint32_t height) {
    device.getDevice().waitIdle();
    createSwapChain(width, height);
}

}
