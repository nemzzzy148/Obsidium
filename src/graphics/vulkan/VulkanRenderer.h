//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <memory>

#include "VulkanBuffer.h"
#include "VulkanCache.h"
#include "VulkanCommandBuffers.h"
#include "VulkanCommandPool.h"
#include "VulkanContext.h"
#include "VulkanDescriptors.h"
#include "VulkanDevice.h"
#include "VulkanFrameContext.h"
#include "VulkanPipeline.h"
#include "VulkanSurface.h"
#include "VulkanSwapChain.h"
#include "../../rhi/Buffer.h"
#include "../../rhi/RendererBackend.h"

namespace obsidium {
class Window;
}

namespace obsidium::vulkan {

class VulkanRenderer : public rhi::RenderBackend {
public:
    explicit VulkanRenderer(Window* window);

    std::unique_ptr<rhi::Buffer> createBuffer(size_t size, BufferType bufferType) override;
    [[nodiscard]] std::unique_ptr<VulkanBuffer> createVulkanBuffer(size_t size, BufferType bufferType) const;
    std::unique_ptr<rhi::Sampler> createSampler(SamplerState samplerState) override;
    std::unique_ptr<rhi::Texture> createTexture(int width, int height,
        TextureUsage textureUsage, TextureFormat format) override;
    std::unique_ptr<rhi::Shader> createShader(std::vector<char> code) override;

    void begin() override;

    void useShader(const rhi::Shader &shader) override;

    void bindUniformBuffer(const rhi::Buffer &buffer, uint32_t binding, uint32_t offset, uint32_t size, ShaderStage shaderStage) override;

    void bindVertexBuffer(const rhi::Buffer &buffer, uint32_t binding, uint32_t offset) override;
    void bindIndexBuffer(const rhi::Buffer &buffer, IndexType indexType, uint32_t offset) override;

    void draw(uint32_t vertexCount, uint32_t firstVertex) override;
    void drawIndexed(uint32_t indexCount, uint32_t firstIndex, uint32_t vertexOffset) override;
    void drawInstanced(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) override;
    void drawIndexedInstanced(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, uint32_t vertexOffset, uint32_t firstInstance) override;
    void drawIndirect(const rhi::Buffer &buffer, uint32_t offset, uint32_t drawCount, uint32_t stride) override;
    void drawIndexedIndirect(const rhi::Buffer &buffer, uint32_t offset, uint32_t drawCount, uint32_t stride) override;

    void end() override;

    void resize(uint32_t width, uint32_t height) override;
    void destroy() override;
private:
    void renderOntoSwapChain(const rhi::RenderPacket& renderPacket);
    Window* window = nullptr;

    void resize() const;

    std::unique_ptr<VulkanContext> context;
    std::unique_ptr<VulkanSurface> surface;
    std::unique_ptr<VulkanDevice> device;
    std::unique_ptr<VulkanSwapChain> swapChain;
    std::unique_ptr<VulkanCommandPool> commandPool;

    std::unique_ptr<VulkanShaderCache> cache;

    uint32_t frameIndex = 0;
    std::vector<VulkanFrameContext> frameContexts;
    void createFrameContexts();
};

}
