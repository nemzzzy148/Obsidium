//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include <utility>

#include "../../include/graphics/Renderer.h"

#include <ranges>

#include "../rhi/RendererBackend.h"
#include "../rhi/RenderPacket.h"
#include "utils/Hash.h"
#include "vulkan/VulkanRenderer.h"

namespace obsidium {

std::unique_ptr<Renderer> Renderer::create(Window* window, MeshManager* assetManager, const Backend backend) {
    auto r = std::unique_ptr<Renderer>(new Renderer());
    switch (backend) {
        case Backend::Vulkan:
            r->backend = std::make_unique<vulkan::VulkanRenderer>(window, assetManager);
            ShaderInstance::initialize(ShaderFormat::SPIRV);
    }
    r->backendType = backend;
    return std::move(r);
}

void Renderer::renderScene(Scene &scene) const {
    rhi::RenderPacket renderPacket = scene.createRenderPacket();
    submitPacket(renderPacket);
}

Buffer Renderer::createBuffer(BufferType type, size_t size) const {
    Buffer buffer = Buffer();
    buffer.buffer = backend->createBuffer(size, type);
    return std::move(buffer);
}

Texture Renderer::createTexture(const Image &image) const {
    auto texture = Texture();
    texture.texture = backend->createTexture(image.data, image.width, image.height);
    texture.hash = hash::fnv1a(image.data, image.width * image.height * sizeof(unsigned char) * DefaultChannels);
    return std::move(texture);
}

void Renderer::resize(const uint32_t width, const uint32_t height) const {
    backend->resize(width, height);
}

void Renderer::destroy() const {
    backend->destroy();
}

void Renderer::submitPacket(rhi::RenderPacket& packet) const {
    backend->submitPacket(packet);
}

}