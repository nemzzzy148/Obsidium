//
// Created by Nemesis Verstraete on 20/07/2026.
//

#pragma once
#include <memory>

#include "../../src/rhi/Buffer.h"

namespace obsidium {

enum class BufferType {
    VertexBuffer,
    IndexBuffer,
    UniformBuffer
};

class Buffer {
public:
    [[nodiscard]] size_t getSize() const;

    void write(const void* data, size_t size, size_t offset);
private:
    Buffer() = default;
    std::unique_ptr<rhi::Buffer> buffer;
    friend class Renderer;
};
}
