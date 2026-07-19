//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include "../../rhi/Buffer.h"

#include <vulkan/vulkan_raii.hpp>

namespace obsidium::vulkan {

class VulkanBuffer : public rhi::Buffer {
public:
    VulkanBuffer(vk::raii::Buffer buffer, vk::raii::DeviceMemory memory, void *memoryPointer, size_t size);
    ~VulkanBuffer() override;
    void destroy() override;
    [[nodiscard]] size_t getSize() const override { return size; }

    vk::raii::Buffer& getBuffer() { return buffer; }

    void write(const void *data, size_t size, size_t offset) override;
private:
    size_t size;
    void* mapped;

    vk::raii::Buffer buffer;
    vk::raii::DeviceMemory memory;
};

}
