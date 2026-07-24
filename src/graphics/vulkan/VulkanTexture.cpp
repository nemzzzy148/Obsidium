//
// Created by Nemesis Verstraete on 20/07/2026.
//

#include "VulkanTexture.h"

namespace obsidium::vulkan {

VulkanTexture::VulkanTexture(vk::raii::Image image, vk::raii::DeviceMemory memory, void* mapped, vk::raii::ImageView view)
    : image(std::move(image)), memory(std::move(memory)), mapped(mapped), view(std::move(view))  {}

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
