//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "VulkanBuffer.h"

namespace obsidium::vulkan {

VulkanBuffer::VulkanBuffer(vk::raii::Buffer buffer, vk::raii::DeviceMemory memory, void *memoryPointer, const size_t size) :
    size(size), mapped(memoryPointer), buffer(std::move(buffer)), memory(std::move(memory)) {}

VulkanBuffer::~VulkanBuffer() {
    VulkanBuffer::destroy();
}

void VulkanBuffer::destroy() {
    memory.unmapMemory();
    buffer = nullptr;
    memory = nullptr;
}

void VulkanBuffer::write(const void *data, const size_t size, size_t offset) {
    memcpy(static_cast<char*>(mapped) + offset, data, size);
}

}
