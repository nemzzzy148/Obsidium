//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace obsidium {

using MeshHandle = uint32_t;

constexpr MeshHandle InvalidMeshHandle = ~0;

using Index = uint32_t;

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 uv;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

struct BufferRegion {
    size_t size = 0;
    uint32_t offset = 0;
};

struct GPUMesh {
    BufferRegion vertexRegion{};
    BufferRegion indexRegion{};

    uint32_t vertexCount{};
    uint32_t indexCount{};
};

struct PushConstants {
    uint16_t textureIndex;
};

}
