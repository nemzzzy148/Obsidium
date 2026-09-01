//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "VulkanRenderer.h"

#include <glfw/glfw3.h>

#include "VulkanBuffer.h"
#include "VulkanDescriptors.h"
#include "VulkanFrameContext.h"
#include "VulkanTexture.h"
#include "../../../include/window/Window.h"
#include "../../../include/assets/AssetManager.h"
#include "../../utils/Logger.h"
#include "world/scene/Camera.h"

namespace obsidium::vulkan {

VulkanRenderer::VulkanRenderer(Window* window) {
    this->window = window;

    auto extensions = window->getRequiredInstanceExtensions();
    context = std::make_unique<VulkanContext>(extensions);
    surface = std::make_unique<VulkanSurface>(*context, window);
    device = std::make_unique<VulkanDevice>(*context, *surface);

    int width, height;
    window->getFrameBufferSize(&width, &height);
    swapChain = std::make_unique<VulkanSwapChain>(*device, *surface, width, height);
    commandPool = std::make_unique<VulkanCommandPool>(*device, device->getGraphicsFamily());
    createFrameContexts();
}

void VulkanRenderer::destroy() {
    device->getDevice().waitIdle();
}

void VulkanRenderer::resize(const uint32_t width, const uint32_t height) {
    if (width == 0 || height == 0) return;
    swapChain->recreate(width, height);
}

void VulkanRenderer::resize() const {
    int width, height;
    window->getFrameBufferSize(&width, &height);
    while (width == 0 || height == 0) {
        window->getFrameBufferSize(&width, &height);
        window->waitEvents();
    }
    swapChain->recreate(width, height);
}

std::unique_ptr<VulkanBuffer> VulkanRenderer::createVulkanBuffer(const size_t size, const BufferType bufferType) const {
    return std::move(device->createVulkanBuffer(size, bufferType));
}

std::unique_ptr<rhi::Buffer> VulkanRenderer::createBuffer(const size_t size, const BufferType bufferType) {
    return std::move(device->createVulkanBuffer(size, bufferType));
}

std::unique_ptr<rhi::Texture> VulkanRenderer::createTexture(const int width, const int height,
        const TextureUsage textureUsage, const TextureFormat format) {
    return std::move(device->createTexture(width, height, textureUsage, format));
}

void transitionImageLayout(const vk::raii::CommandBuffer &commandBuffer,
                           const vk::raii::Image &image,
                           const vk::ImageLayout oldLayout,
                           const vk::ImageLayout newLayout) {
    vk::ImageMemoryBarrier barrier{
        .oldLayout = oldLayout,
        .newLayout = newLayout,
        .srcQueueFamilyIndex = vk::QueueFamilyIgnored,
        .dstQueueFamilyIndex = vk::QueueFamilyIgnored,
        .image = image,
        .subresourceRange = {.aspectMask = vk::ImageAspectFlagBits::eColor, .levelCount = 1, .layerCount = 1}
    };

    vk::PipelineStageFlagBits srcStage;
    vk::PipelineStageFlagBits dstStage;

    if (oldLayout == vk::ImageLayout::eUndefined && newLayout == vk::ImageLayout::eTransferDstOptimal) {
        barrier.srcAccessMask = {};
        barrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;

        srcStage = vk::PipelineStageFlagBits::eTopOfPipe;
        dstStage = vk::PipelineStageFlagBits::eTransfer;
    }
    else if (oldLayout == vk::ImageLayout::eTransferDstOptimal && newLayout == vk::ImageLayout::eShaderReadOnlyOptimal) {
        barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
        barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

        srcStage = vk::PipelineStageFlagBits::eTransfer;
        dstStage = vk::PipelineStageFlagBits::eFragmentShader;
    }
    else {
        LOG_FATAL("unsupported vulkan layout transition!");
    }

    commandBuffer.pipelineBarrier(srcStage, dstStage, {}, {}, {}, barrier);
}

std::unique_ptr<rhi::Shader> VulkanRenderer::createShader(std::vector<char> code) {

}

void transitionImageLayout(
    const vk::raii::CommandBuffer &commandBuffer,
    const vk::Image &image,
    vk::ImageLayout oldLayout,
    vk::ImageLayout newLayout,
    vk::AccessFlags2 srcAccessMask,
    vk::AccessFlags2 dstAccessMask,
    vk::PipelineStageFlags2 srcStageMask,
    vk::PipelineStageFlags2 dstStageMask,
    vk::ImageAspectFlagBits imageAspectFlags
    ) {
    vk::ImageMemoryBarrier2 barrier = {
        .srcStageMask = srcStageMask,
        .srcAccessMask = srcAccessMask,
        .dstStageMask = dstStageMask,
        .dstAccessMask = dstAccessMask,
        .oldLayout = oldLayout,
        .newLayout = newLayout,
        .srcQueueFamilyIndex = vk::QueueFamilyIgnored,
        .dstQueueFamilyIndex = vk::QueueFamilyIgnored,
        .image = image,
        .subresourceRange = {
            .aspectMask = imageAspectFlags,
            .baseMipLevel = 0,
            .levelCount = 1,
            .baseArrayLayer = 0,
            .layerCount = 1
        }
    };

    vk::DependencyInfo dependencyInfo{
        .dependencyFlags = {},
        .imageMemoryBarrierCount = 1,
        .pImageMemoryBarriers = &barrier
    };
    commandBuffer.pipelineBarrier2(dependencyInfo);
}

void VulkanRenderer::begin() {
    const auto& frameContext = frameContexts[frameIndex];

    if (const auto fenceResult = device->getDevice().waitForFences(*frameContext.inFlightFence, vk::True, UINT64_MAX); fenceResult != vk::Result::eSuccess) {
        LOG_FATAL("failed to wait for vulkan fence");
    }

    auto [result, imageIndex] = swapChain->getHandle().acquireNextImage(UINT64_MAX,
        frameContext.presentCompleteSemaphore, nullptr);
    swapChain->imageIndex = imageIndex;

    if (result == vk::Result::eErrorOutOfDateKHR) {
        resize();
        return;
    }
    if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR) {
        assert(result == vk::Result::eTimeout || result == vk::Result::eNotReady);
        LOG_FATAL("failed to acquire vulkan swap chain image!");
    }

    device->getDevice().resetFences(*frameContext.inFlightFence);

    frameContext.commandBuffer.begin({});

    transitionImageLayout(frameContext.commandBuffer,
        swapChain->getImages()[imageIndex],
        vk::ImageLayout::eUndefined,
        vk::ImageLayout::eColorAttachmentOptimal,
        {},
        vk::AccessFlagBits2::eColorAttachmentWrite,
        vk::PipelineStageFlagBits2::eColorAttachmentOutput,
        vk::PipelineStageFlagBits2::eColorAttachmentOutput,
        vk::ImageAspectFlagBits::eColor
    );

    vk::ClearValue clrColor = vk::ClearColorValue(clearColor.x, clearColor.y, clearColor.z, 1.0f );
    vk::RenderingAttachmentInfo attachmentInfo{
        .imageView = swapChain->getImageViews()[imageIndex],
        .imageLayout = vk::ImageLayout::eColorAttachmentOptimal,
        .loadOp = vk::AttachmentLoadOp::eClear,
        .storeOp = vk::AttachmentStoreOp::eStore,
        .clearValue = clrColor
    };
    vk::RenderingInfo renderingInfo{
        .renderArea = {.offset = {0, 0}, .extent = { swapChain->getExtent().width, swapChain->getExtent().height }},
        .layerCount = 1,
        .colorAttachmentCount = 1,
        .pColorAttachments = &attachmentInfo
    };

    frameContext.commandBuffer.beginRendering(renderingInfo);

    frameContext.commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, frameContext.pipeline.getHandle());
    frameContext.commandBuffer.setViewport(0, vk::Viewport(0.0f, 0.0f,
        static_cast<uint32_t>(swapChain->getExtent().width), static_cast<uint32_t>(swapChain->getExtent().height),
        0.0f, 1.0f));
    frameContext.commandBuffer.setScissor(0, vk::Rect2D(vk::Offset2D(0,0), swapChain->getExtent()));
    frameContext.commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipelineLayout->getHandle(), 0, *frameContext.descriptorSet, nullptr);

}

void VulkanRenderer::useShader(const rhi::Shader &shader) {
}

void VulkanRenderer::bindUniformBuffer(const rhi::Buffer &buffer, uint32_t binding, uint32_t offset, uint32_t size,
    ShaderStage shaderStage) {
}

void VulkanRenderer::bindVertexBuffer(const rhi::Buffer &buffer, uint32_t binding, uint32_t offset) {
}

void VulkanRenderer::bindIndexBuffer(const rhi::Buffer &buffer, IndexType indexType, uint32_t offset) {
}

void VulkanRenderer::draw(uint32_t vertexCount, uint32_t firstVertex) {
}

void VulkanRenderer::drawIndexed(uint32_t indexCount, uint32_t firstIndex, uint32_t vertexOffset) {
}

void VulkanRenderer::drawInstanced(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex,
    uint32_t firstInstance) {
}

void VulkanRenderer::drawIndexedInstanced(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex,
    uint32_t vertexOffset, uint32_t firstInstance) {
}

void VulkanRenderer::drawIndirect(const rhi::Buffer &buffer, uint32_t offset, uint32_t drawCount, uint32_t stride) {
}

void VulkanRenderer::drawIndexedIndirect(const rhi::Buffer &buffer, uint32_t offset, uint32_t drawCount,
    uint32_t stride) {
}

void VulkanRenderer::end() {
    const auto& frameContext = frameContexts[frameIndex];
    frameContext.commandBuffer.endRendering();

    transitionImageLayout(frameContext.commandBuffer,
        swapChain->getImages()[swapChain->imageIndex],
        vk::ImageLayout::eColorAttachmentOptimal,
        vk::ImageLayout::ePresentSrcKHR,
        vk::AccessFlagBits2::eColorAttachmentWrite,
        {},
        vk::PipelineStageFlagBits2::eColorAttachmentOutput,
        vk::PipelineStageFlagBits2::eBottomOfPipe,
        vk::ImageAspectFlagBits::eColor
    );

    frameContext.commandBuffer.end();

    // presentation info

    vk::PipelineStageFlags waitDestinationStageFlags( vk::PipelineStageFlagBits::eColorAttachmentOutput );
    vk::SubmitInfo submitInfo{
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &*frameContext.presentCompleteSemaphore,
        .pWaitDstStageMask = &waitDestinationStageFlags,
        .commandBufferCount = 1,
        .pCommandBuffers = &*frameContext.commandBuffer,
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = &*swapChain->getPresentCompleteSemaphores()[swapChain->imageIndex]
    };

    device->getGraphicsQueue().submit(submitInfo, *frameContext.inFlightFence);

    const vk::PresentInfoKHR presentInfo{
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &*swapChain->getPresentCompleteSemaphores()[swapChain->imageIndex],
        .swapchainCount = 1,
        .pSwapchains = &*swapChain->getHandle(),
        .pImageIndices = &swapChain->imageIndex
    };

    if (const vk::Result result = device->getGraphicsQueue().presentKHR(presentInfo); result == vk::Result::eSuboptimalKHR || result == vk::Result::eErrorOutOfDateKHR) {
        resize();
    }
    else {
        assert(result == vk::Result::eSuccess);
    }
}

}