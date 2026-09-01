//
// Created by Nemesis Verstraete on 20/07/2026.
//

#include "VulkanTexture.h"

#include "VulkanRenderer.h"

namespace obsidium::vulkan {

VulkanSampler::VulkanSampler(VulkanDevice& device, const SamplerState state) : state(state) {
    auto mode = vk::SamplerAddressMode::eRepeat;
    switch (state.samplerWrap) {
        case SamplerWrap::Repeat:
            mode = vk::SamplerAddressMode::eRepeat;
            break;
        case SamplerWrap::Clamp:
            mode = vk::SamplerAddressMode::eClampToEdge;
            break;
        case SamplerWrap::Mirror:
            mode = vk::SamplerAddressMode::eMirroredRepeat;
            break;
        case SamplerWrap::Border:
            mode = vk::SamplerAddressMode::eClampToBorder;
            break;
    }
    bool anisotropy = false;
    auto filter = vk::Filter::eLinear;
    switch (state.samplerFilter) {
        case SamplerFilter::Point:
            filter = vk::Filter::eNearest;
            break;
        case SamplerFilter::Linear:
            filter = vk::Filter::eLinear;
            break;
        case SamplerFilter::Anisotropic:
            anisotropy = true;
            break;
    }
    const auto properties = device.getPhysicalDevice().getProperties();
    const vk::SamplerCreateInfo createInfo {
        .magFilter = filter,
        .minFilter = vk::Filter::eLinear,
        .mipmapMode = vk::SamplerMipmapMode::eLinear,
        .addressModeU = mode,
        .addressModeV = mode,
        .addressModeW = mode,
        .anisotropyEnable = anisotropy,
        .maxAnisotropy = properties.limits.maxSamplerAnisotropy,
        .compareEnable = vk::False,
        .compareOp = vk::CompareOp::eAlways,
    };
    sampler = vk::raii::Sampler(device.getDevice(), createInfo);
}

VulkanTexture::VulkanTexture(VulkanRenderer& renderer, vk::raii::Image image, vk::raii::DeviceMemory memory,
                             void* mapped, vk::raii::ImageView view, const TextureFormat format, const TextureUsage usage)
        : image(std::move(image)), memory(std::move(memory)), mapped(mapped),
        view(std::move(view)), renderer(renderer) {
    this->format = format;
    this->usage = usage;
}

void VulkanTexture::unmapMemory() {
    memory.unmapMemory();
    mapped = nullptr;
}

void VulkanTexture::destroy() {
    memory.unmapMemory();
    view = nullptr;
    memory = nullptr;
    image = nullptr;
}

VulkanTexture::~VulkanTexture() {
    VulkanTexture::destroy();
}

}
