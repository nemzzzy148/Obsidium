//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <cstdint>

#include "../../Renderium/include/Buffer.h"
#include "../rhi/RenderPacket.h"
#include "../rhi/Shader.h"
#include "../rhi/Texture.h"
#include "../graphics/shader/Shader.h"
#include "graphics/Buffer.h"
#include "graphics/Renderer.h"
#include "graphics/Shader.h"

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
    virtual std::unique_ptr<Sampler> createSampler(SamplerState samplerState) = 0;
    virtual std::unique_ptr<Texture> createTexture(int width, int height,
        TextureUsage textureUsage, TextureFormat format) = 0;
    virtual std::unique_ptr<Shader> createShader(std::vector<char> userCode) = 0;

    virtual void begin() = 0;

    virtual void useMaterial(const Material& material) = 0;
    virtual void useShader(const Shader& shader) = 0;

    virtual void bindTexture(const Texture& texture, uint32_t binding, ShaderStage shaderStage = ShaderStage::Fragment) = 0;
    virtual void bindSampler(const Sampler& sampler, uint32_t binding, ShaderStage shaderStage = ShaderStage::Fragment) = 0;

    virtual void bindUniformBuffer(const Buffer& buffer, uint32_t binding,
        uint32_t offset = 0, uint32_t size = 0, ShaderStage shaderStage = ShaderStage::All) = 0;

    virtual void bindVertexBuffer(const Buffer& buffer, uint32_t binding = 0, uint32_t offset = 0) = 0;
    virtual void bindIndexBuffer(const Buffer& buffer, IndexType indexType = IndexType::UInt32, uint32_t offset = 0) = 0;

    virtual void draw(uint32_t vertexCount, uint32_t firstVertex = 0) = 0;
    virtual void drawIndexed(uint32_t indexCount, uint32_t firstIndex = 0, uint32_t vertexOffset = 0) = 0;
    virtual void drawInstanced(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex = 0, uint32_t firstInstance = 0) = 0;
    virtual void drawIndexedInstanced(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex = 0,
        uint32_t vertexOffset = 0, uint32_t firstInstance = 0) = 0;
    virtual void drawIndirect(const Buffer& buffer, uint32_t offset, uint32_t drawCount, uint32_t stride) = 0;
    virtual void drawIndexedIndirect(const Buffer& buffer, uint32_t offset, uint32_t drawCount, uint32_t stride) = 0;

    virtual void end() = 0;

    static constexpr uint32_t MAX_FRAMES_IN_FLIGHT = 3;
    glm::vec3 clearColor = { 0.0f, 0.0f, 0.0f };
};

}
