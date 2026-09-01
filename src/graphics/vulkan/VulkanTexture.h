//
// Created by Nemesis Verstraete on 20/07/2026.
//

#pragma once
#include <vulkan/vulkan_raii.hpp>

#include "../../rhi/Texture.h"
#include "../../rhi/Sampler.h"
#include "graphics/SamplerState.h"

namespace obsidium::vulkan {

class VulkanDevice;
class VulkanSampler : public rhi::Sampler {
public:
    explicit VulkanSampler(VulkanDevice& device, SamplerState state);

    [[nodiscard]] vk::raii::Sampler& getHandle() { return sampler; }

    bool operator==(const VulkanSampler& other) const {
        return state == other.state;
    }
private:
    SamplerState state;
    vk::raii::Sampler sampler = nullptr;
};

class VulkanRenderer;
class VulkanTexture : public rhi::Texture {
public:
    VulkanTexture(VulkanRenderer& renderer, vk::raii::Image image, vk::raii::DeviceMemory memory,
        void* mapped, vk::raii::ImageView view, TextureFormat format, TextureUsage usage);

    [[nodiscard]] vk::raii::Image& getImage() { return image; }
    [[nodiscard]] vk::raii::ImageView& getView() { return view; }

    void unmapMemory();

    void destroy() override;
    ~VulkanTexture() override;
private:
    vk::raii::Image image = nullptr;
    vk::raii::DeviceMemory memory = nullptr;
    void* mapped = nullptr;
    vk::raii::ImageView view = nullptr;

    VulkanRenderer& renderer;

    friend class VulkanRenderer;
};

}
