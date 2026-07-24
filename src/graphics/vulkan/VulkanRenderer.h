//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <memory>

#include "VulkanBuffer.h"
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
    VulkanRenderer(Window* window);
    void destroy() override;
    void submitPacket(rhi::RenderPacket& packet) override;
    void resize(uint32_t width, uint32_t height) override;
    [[nodiscard]] std::unique_ptr<VulkanBuffer> createVulkanBuffer(size_t size, BufferType bufferType) const;
    std::unique_ptr<rhi::Buffer> createBuffer(size_t size, BufferType bufferType) override;
    std::unique_ptr<rhi::Texture> createTexture(unsigned char* data, int width, int height) override;
private:
    void executeFrameContext(VulkanFrameContext& frameContext, rhi::RenderPacket& renderPacket) const;

    vk::MemoryPropertyFlags bufferAllocationMemoryProperties = vk::MemoryPropertyFlagBits::eHostVisible |
        vk::MemoryPropertyFlagBits::eHostCoherent;
    [[nodiscard]] uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties) const;

    Window* window = nullptr;

    void resize() const;

    std::unique_ptr<VulkanContext> context;
    std::unique_ptr<VulkanSurface> surface;
    std::unique_ptr<VulkanDevice> device;
    std::unique_ptr<VulkanSwapChain> swapChain;

    std::unique_ptr<VulkanDescriptorSetLayout> descriptorSetLayout;
    std::unique_ptr<VulkanPipelineLayout> pipelineLayout;
    std::unique_ptr<VulkanPipeline> pipeline;
    std::unique_ptr<VulkanDescriptorPool> descriptorPool;

    std::unique_ptr<VulkanCommandPool> commandPool;

    uint32_t frameIndex = 0;
    std::vector<VulkanFrameContext> frameContexts;
    void createFrameContexts();
};

}
