//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <cstdint>

#include "Buffer.h"
#include "RenderPacket.h"
#include "../graphics/shader/Shader.h"

namespace obsidium {

class Window;
class MeshManager;

}

namespace obsidium::rhi {

class RenderBackend {
public:
    virtual ~RenderBackend();
    virtual void destroy() = 0;
    virtual void submitPacket(RenderPacket& packet) = 0;
    virtual void resize(uint32_t width, uint32_t height) = 0;
    virtual std::unique_ptr<Buffer> createBuffer(size_t size, BufferType bufferType) = 0;

    static constexpr uint32_t MAX_FRAMES_IN_FLIGHT = 3;
    glm::vec3 clearColor = { 0.0f, 0.0f, 0.0f };

    MeshManager* assetManager = nullptr;
};

}
