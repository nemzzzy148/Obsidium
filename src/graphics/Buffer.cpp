//
// Created by Nemesis Verstraete on 20/07/2026.
//

#include "../../include/graphics/Buffer.h"
#include "../../src/rhi/Buffer.h"

#include "graphics/Renderer.h"

namespace obsidium {

Buffer::Buffer(std::unique_ptr<rhi::Buffer> buffer) : buffer(std::move(buffer)) {}

Buffer Buffer::create(const Renderer &renderer, const BufferType type, const size_t size) {
    return renderer.createBuffer(type, size);
}

size_t Buffer::getSize() const {
    return buffer->getSize();
}

void Buffer::write(const void *data, const size_t size, const size_t offset) const {
    buffer->write(data, size, offset);
}

}
