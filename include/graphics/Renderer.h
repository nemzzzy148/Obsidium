//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <memory>

#include "Buffer.h"
#include "../../src/rhi/RendererBackend.h"
#include "../scene/SceneManager.h"

namespace obsidium {

class Engine;
class MeshManager;

class Renderer {
public:
    enum class Backend { Vulkan };
    ~Renderer() = default;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    [[nodiscard]] rhi::RenderBackend* getBackend() const { return backend.get(); }

    // auto rendering
    void submitPacket(rhi::RenderPacket& packet) const;
    void renderScene(Scene& scene) const;

    [[nodiscard]] Buffer createBuffer(BufferType type, size_t size) const;
    [[nodiscard]] Texture createTexture(const Image& image) const;

    void destroy() const;
private:
    static std::unique_ptr<Renderer> create(Window* window, MeshManager* assetManager, Backend backend = Backend::Vulkan);
    Backend backendType = Backend::Vulkan;

    void resize(uint32_t width, uint32_t height) const;

    Renderer() = default;
    std::unique_ptr<rhi::RenderBackend> backend;

    friend class Engine;
};

}
