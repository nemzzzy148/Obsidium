//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include <utility>

#include "../../include/graphics/Renderer.h"

#include "../rhi/RendererBackend.h"
#include "utils/Hash.h"
#include "vulkan/VulkanRenderer.h"
#include "../../include/graphics/Texture.h"
#include "../rhi/Sampler.h"
#include "graphics/Sampler.h"
#include "graphics/Shader.h"
#include "graphics/ShaderCompiler.h"

namespace obsidium {

Renderer::Renderer(Window *window, const Backend rendererBackend) : backendType(rendererBackend) {
    switch (rendererBackend) {
        case Backend::Vulkan:
            backend = std::make_unique<vulkan::VulkanRenderer>(window);
    }
    initializeShaderCompiler();
}

void Renderer::initializeShaderCompiler() const {
    switch (backendType) {
        case Backend::Vulkan:
            ShaderCompiler::initialize(ShaderFormat::SPIRV);
            break;
    }

}

void Renderer::useMaterial(const Material &material) const {
    backend->useMaterial(material);
}

Buffer Renderer::createBuffer(const BufferType type, const size_t size) const {
    return Buffer(std::move(backend->createBuffer(size, type)));
}

Sampler Renderer::createSampler(const SamplerState samplerState) const {
    return Sampler(std::move(backend->createSampler(samplerState)));
}

Texture Renderer::createTexture(const uint32_t width, const uint32_t height,
        const TextureUsage textureUsage, const TextureFormat format) const {
    return Texture(std::move(backend->createTexture(width, height, textureUsage, format)));
}

Shader Renderer::createShader(std::vector<char> userCode) const {
    Shader shader = backend->createShader(std::move(userCode));
    return std::move(shader);
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

void Renderer::begin() const {
    backend->begin();
}

void Renderer::useShader(const Shader &shader) const {
    backend->useShader(shader.getBackend());
}

void Renderer::bindUniformBuffer(const Buffer &buffer, const uint32_t binding, const uint32_t offset,
    const uint32_t size, const ShaderStage shaderStage) const {
    backend->bindUniformBuffer(buffer.getBackend(), binding, offset, size, shaderStage);
}

void Renderer::bindTexture(const Texture &texture, const uint32_t binding, const ShaderStage shaderStage) const {
    backend->bindTexture(texture.getBackend(), binding, shaderStage);
}

void Renderer::bindSampler(const Sampler &sampler, const uint32_t binding, const ShaderStage shaderStage) const {
    backend->bindSampler(sampler.getBackend(), binding, shaderStage);
}

void Renderer::bindVertexBuffer(const Buffer &buffer, const uint32_t binding, const uint32_t offset) const {
    backend->bindVertexBuffer(buffer.getBackend(), binding, offset);
}

void Renderer::bindIndexBuffer(const Buffer &buffer, const IndexType indexType, const uint32_t offset) const {
    backend->bindIndexBuffer(buffer.getBackend(), indexType, offset);
}

void Renderer::draw(const uint32_t vertexCount, const uint32_t firstVertex) const {
    backend->draw(vertexCount, firstVertex);
}

void Renderer::drawIndexed(const uint32_t indexCount, const uint32_t firstIndex, const uint32_t vertexOffset) const {
    backend->drawIndexed(indexCount, firstIndex, vertexOffset);
}

void Renderer::drawInstanced(const uint32_t vertexCount, const uint32_t instanceCount, const uint32_t firstVertex,
    const uint32_t firstInstance) const {
    backend->drawInstanced(vertexCount, instanceCount, firstVertex, firstInstance);
}

void Renderer::drawIndexedInstanced(const uint32_t indexCount, const uint32_t instanceCount, const uint32_t firstIndex,
    const uint32_t vertexOffset, const uint32_t firstInstance) const {
    backend->drawIndexedInstanced(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

void Renderer::drawIndirect(const Buffer& buffer, const uint32_t offset, const uint32_t drawCount, const uint32_t stride) const {
    backend->drawIndirect(buffer.getBackend(), offset, drawCount, stride);
}

void Renderer::drawIndexedIndirect(const Buffer &buffer, const uint32_t offset, const uint32_t drawCount, const uint32_t stride) const {
    backend->drawIndexedIndirect(buffer.getBackend(), offset, drawCount, stride);
}

void Renderer::end() const {
    backend->end();
}

}