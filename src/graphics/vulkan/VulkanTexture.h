//
// Created by Nemesis Verstraete on 20/07/2026.
//

#pragma once
#include "../../rhi/Texture.h"
#include <vulkan/vulkan_raii.hpp>

namespace obsidium::vulkan {

class VulkanTexture : public rhi::Texture {
public:
    VulkanTexture(vk::raii::Image image, vk::raii::DeviceMemory memory, void* mapped, vk::raii::ImageView view);

    void destroy() override;
    ~VulkanTexture();
private:
    vk::raii::Image image = nullptr;
    vk::raii::DeviceMemory memory = nullptr;
    void* mapped = nullptr;
    vk::raii::ImageView view = nullptr;
};

}
