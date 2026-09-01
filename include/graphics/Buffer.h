//
// Created by Nemesis Verstraete on 20/07/2026.
//

#pragma once
#include <memory>

#include "../../src/utils/RefCounter.h"

namespace obsidium {

namespace rhi {
class Buffer;
}

class Renderer;

enum class BufferType {
    VertexBuffer,
    IndexBuffer,
    UniformBuffer,
    ShaderStorageBuffer
};

class Buffer : public RefCounter {
public:
    static Buffer create(const Renderer& renderer, BufferType type, size_t size);

    [[nodiscard]] size_t getSize() const;

    void write(const void* data, size_t size, size_t offset = 0) const;
private:
    explicit Buffer(std::unique_ptr<rhi::Buffer> buffer);
    rhi::Buffer& getBackend() const { return *buffer; }
    std::unique_ptr<rhi::Buffer> buffer;
    friend class Renderer;
};

}
