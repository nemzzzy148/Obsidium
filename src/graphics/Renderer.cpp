//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include <utility>

#include "../../include/graphics/Renderer.h"

#include "../rhi/RendererBackend.h"
#include "../rhi/RenderPacket.h"
#include "utils/Hash.h"
#include "vulkan/VulkanRenderer.h"
#include "../../include/graphics/Texture.h"

namespace obsidium {

Renderer::Renderer(Window *window, const Backend rendererBackend) : backendType(rendererBackend) {
    switch (rendererBackend) {
        case Backend::Vulkan:
            backend = std::make_unique<vulkan::VulkanRenderer>(window);
            ShaderInstance::initialize(ShaderFormat::SPIRV);
    }
}

Buffer Renderer::createBuffer(const BufferType type, const size_t size) const {
    auto buffer = Buffer();
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