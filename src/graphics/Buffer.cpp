//
// Created by Nemesis Verstraete on 20/07/2026.
//

#include "../../include/graphics/Buffer.h"

namespace obsidium {

size_t Buffer::getSize() const {
    return buffer->getSize();
}

void Buffer::write(const void *data, const size_t size, const size_t offset) const {
    buffer->write(data, size, offset);
}

}
