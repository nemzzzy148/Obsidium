//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <memory>

#include "../../src/rhi/RendererBackend.h"


namespace obsidium {

class Window;
class Buffer;
class Texture;
class Image;

class Renderer {
public:
    enum class Backend { Vulkan };
    ~Renderer() = default;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    explicit Renderer(Window* window, Backend rendererBackend = Backend::Vulkan);

    [[nodiscard]] rhi::RenderBackend* getBackend() const { return backend.get(); }

    // auto rendering
    void submitPacket(rhi::RenderPacket& packet) const;

    [[nodiscard]] Buffer createBuffer(BufferType type, size_t size) const;
    [[nodiscard]] Texture createTexture(const Image& image) const;

    void destroy() const;
private:
    Backend backendType = Backend::Vulkan;

    void resize(uint32_t width, uint32_t height) const;

    std::unique_ptr<rhi::RenderBackend> backend;

    friend class Engine;
};

}
