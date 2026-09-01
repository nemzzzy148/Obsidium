//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <memory>

#include <vector>

#include "Sampler.h"
#include "Texture.h"

namespace obsidium {
class Material;

enum class BufferType;
struct SamplerState;

class Window;
class Buffer;
class Texture;
class Image;
class Shader;

namespace rhi {
struct RenderPacket;
class RenderBackend;
}

enum class ShaderStage : uint32_t {
    Vertex = 1 << 0,
    Fragment = 1 << 1,
    Compute = 1 << 2,
    All = Vertex | Fragment | Compute
};

enum class IndexType { UInt16, UInt32 };

struct RendererCreateInfo {

};

class Renderer {
public:
    enum class Backend { Vulkan };
    ~Renderer() = default;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    explicit Renderer(Window* window, Backend rendererBackend = Backend::Vulkan);
    void initializeShaderCompiler() const;

    [[nodiscard]] rhi::RenderBackend* getBackend() const { return backend.get(); }

    // auto rendering
    void submitPacket(rhi::RenderPacket& packet) const;

    // manual rendering
    void begin() const;

    void useShader(const Shader& shader) const;
    void useMaterial(const Material& material) const;

    void bindUniformBuffer(const Buffer& buffer, uint32_t binding,
        uint32_t offset = 0, uint32_t size = 0, ShaderStage shaderStage = ShaderStage::All) const;

    void bindTexture(const Texture& texture, uint32_t binding, ShaderStage shaderStage = ShaderStage::Fragment) const;
    void bindSampler(const Sampler& sampler, uint32_t binding, ShaderStage shaderStage = ShaderStage::Fragment) const;

    void bindVertexBuffer(const Buffer& buffer, uint32_t binding = 0, uint32_t offset = 0) const;
    void bindIndexBuffer(const Buffer& buffer, IndexType indexType = IndexType::UInt32, uint32_t offset = 0) const;

    void draw(uint32_t vertexCount, uint32_t firstVertex = 0) const;
    void drawIndexed(uint32_t indexCount, uint32_t firstIndex = 0, uint32_t vertexOffset = 0) const;
    void drawInstanced(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex = 0, uint32_t firstInstance = 0) const;
    void drawIndexedInstanced(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex = 0, uint32_t vertexOffset = 0, uint32_t firstInstance = 0) const;
    void drawIndirect(const Buffer& buffer, uint32_t offset, uint32_t drawCount, uint32_t stride) const;
    void drawIndexedIndirect(const Buffer& buffer, uint32_t offset, uint32_t drawCount, uint32_t stride) const;

    void end() const;

    [[nodiscard]] Buffer createBuffer(BufferType type, size_t size) const;
    [[nodiscard]] Texture createTexture(uint32_t width, uint32_t height, TextureUsage textureUsage, TextureFormat format) const;
    [[nodiscard]] Sampler createSampler(SamplerState samplerState) const;
    [[nodiscard]] Shader createShader(std::vector<char> userCode) const;

    void destroy() const;
private:
    void resize(uint32_t width, uint32_t height) const;

    Backend backendType = Backend::Vulkan;
    std::unique_ptr<rhi::RenderBackend> backend;
};

}
