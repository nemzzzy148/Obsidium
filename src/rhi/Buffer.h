//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <glm/glm.hpp>

namespace obsidium::rhi {

class Buffer {
public:
    virtual ~Buffer() = default;

    virtual void destroy() = 0;
    [[nodiscard]] virtual size_t getSize() const = 0;
    virtual void write(const void* data, size_t size, size_t offset) = 0;
};

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

}
