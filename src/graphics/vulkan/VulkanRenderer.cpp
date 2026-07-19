//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "VulkanRenderer.h"

#include <glfw/glfw3.h>

#include "VulkanBuffer.h"
#include "VulkanDescriptors.h"
#include "VulkanFrameContext.h"
#include "../../../include/core/Window.h"
#include "../../../include/graphics/MeshManager.h"

namespace obsidium::vulkan {

VulkanRenderer::VulkanRenderer(Window* window, MeshManager* assetManager) {
    this->assetManager = assetManager;

    auto extensions = window->getRequiredInstanceExtensions();
    context = std::make_unique<VulkanContext>(extensions);
    surface = std::make_unique<VulkanSurface>(*context, window);
    device = std::make_unique<VulkanDevice>(*context, *surface);

    int width, height;
    window->getFrameBufferSize(&width, &height);
    swapChain = std::make_unique<VulkanSwapChain>(*device, *surface, width, height);

    descriptorSetLayout = std::make_unique<VulkanDescriptorSetLayout>(*device);
    pipelineLayout = std::make_unique<VulkanPipelineLayout>(*device, *descriptorSetLayout);
    pipeline = std::make_unique<VulkanPipeline>(*device, *swapChain, *pipelineLayout, ShaderInstance::generateCode("../shader/mainShader.slang"));
    descriptorPool = std::make_unique<VulkanDescriptorPool>(*device, MAX_FRAMES_IN_FLIGHT);
    commandPool = std::make_unique<VulkanCommandPool>(*device, device->getGraphicsFamily());

    createFrameContexts();
}

void VulkanRenderer::destroy() {
    device->getDevice().waitIdle();
}


void VulkanRenderer::submitPacket(rhi::RenderPacket& packet) {
    executeFrameContext(frameContexts[frameIndex], packet);
    frameIndex =  (frameIndex + 1) % MAX_FRAMES_IN_FLIGHT;
}

void VulkanRenderer::resize(uint32_t width, uint32_t height) {

}

uint32_t VulkanRenderer::findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties) const {
    const vk::PhysicalDeviceMemoryProperties memoryProperties = device->getPhysicalDevice().getMemoryProperties();

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type");
}

std::unique_ptr<VulkanBuffer> VulkanRenderer::createVulkanBuffer(size_t size, rhi::BufferType bufferType) {
    vk::BufferUsageFlags usage;

    switch (bufferType) {
        case rhi::BufferType::IndexBuffer:
            usage = vk::BufferUsageFlagBits::eIndexBuffer;
            break;
        case rhi::BufferType::VertexBuffer:
            usage = vk::BufferUsageFlagBits::eVertexBuffer;
            break;
        case rhi::BufferType::UniformBuffer:
            usage = vk::BufferUsageFlagBits::eUniformBuffer;
            break;
    }
    vk::BufferCreateInfo bufferInfo{
        .size = size,
        .usage = usage,
        .sharingMode = vk::SharingMode::eExclusive
    };
    vk::raii::Buffer buffer = vk::raii::Buffer(device->getDevice(), bufferInfo);

    vk::MemoryRequirements memoryRequirements = buffer.getMemoryRequirements();
    vk::MemoryAllocateInfo allocInfo{
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = findMemoryType(memoryRequirements.memoryTypeBits, bufferAllocationMemoryProperties)
    };
    vk::raii::DeviceMemory bufferMemory = vk::raii::DeviceMemory(device->getDevice(), allocInfo);
    buffer.bindMemory(bufferMemory, 0);

    return std::make_unique<VulkanBuffer>(std::move(buffer), std::move(bufferMemory),
        bufferMemory.mapMemory(0, size), size);
}

std::unique_ptr<rhi::Buffer> VulkanRenderer::createBuffer(size_t size, rhi::BufferType bufferType) {
    return std::move(createVulkanBuffer(size, bufferType));
}

void transitionImageLayout(vk::raii::CommandBuffer &commandBuffer,
    const vk::raii::Image &image,
    vk::ImageLayout oldLayout,
    vk::ImageLayout newLayout) {
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
        throw std::runtime_error("unsupported layout transition!");
    }

    commandBuffer.pipelineBarrier(srcStage, dstStage, {}, {}, {}, barrier);
}

void transitionImageLayout(
    vk::raii::CommandBuffer &commandBuffer,
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

void VulkanRenderer::executeFrameContext(VulkanFrameContext& frameContext, rhi::RenderPacket& renderPacket) const {
    // update uniform buffer
    rhi::UniformBufferObject ubo{};
    ubo.proj = renderPacket.camera.first->getProjectionMat();
    ubo.proj[1][1] *= -1;
    ubo.view = renderPacket.camera.second;
    auto fenceResult = device->getDevice().waitForFences(*frameContext.inFlightFence, vk::True, UINT64_MAX);
    if (fenceResult != vk::Result::eSuccess) {
        throw std::runtime_error("failed to wait for fence");
    }

    auto [result, imageIndex] = swapChain->getHandle().acquireNextImage(UINT64_MAX,
        frameContext.presentCompleteSemaphore, nullptr);

    if (result == vk::Result::eErrorOutOfDateKHR) {
        //resize needed
        return;
    }
    if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR) {
        assert(result == vk::Result::eTimeout || result == vk::Result::eNotReady);
        throw std::runtime_error("failed to acquire swap chain image!");
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

    auto* vertexBuffer = static_cast<VulkanBuffer*>(assetManager->getVertexBuffer());
    auto* indexBuffer = static_cast<VulkanBuffer*>(assetManager->getIndexBuffer());
    frameContext.commandBuffer.bindVertexBuffers(0, *vertexBuffer->getBuffer(), {0});
    frameContext.commandBuffer.bindIndexBuffer(*indexBuffer->getBuffer(), 0, vk::IndexType::eUint32);

    for (const auto&[handle, model] : renderPacket.meshes) {
        GPUMesh mesh = assetManager->getMesh(handle);
        if (mesh.hash == ~0) continue;
        ubo.model = model;
        frameContext.uniformBuffer->write(&ubo, sizeof(ubo), 0);
        frameContext.commandBuffer.drawIndexed(mesh.indexCount, 1,
            mesh.indexRegion.offset * sizeof(Index), mesh.vertexRegion.offset, 0);
    }

    frameContext.commandBuffer.endRendering();

    transitionImageLayout(frameContext.commandBuffer,
        swapChain->getImages()[imageIndex],
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
        .pSignalSemaphores = &*swapChain->getPresentCompleteSemaphores()[imageIndex]
    };

    device->getGraphicsQueue().submit(submitInfo, *frameContext.inFlightFence);

    const vk::PresentInfoKHR presentInfo{
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &*swapChain->getPresentCompleteSemaphores()[imageIndex],
        .swapchainCount = 1,
        .pSwapchains = &*swapChain->getHandle(),
        .pImageIndices = &imageIndex
    };

    result = device->getGraphicsQueue().presentKHR(presentInfo);

    if (result == vk::Result::eSuboptimalKHR || result == vk::Result::eErrorOutOfDateKHR) {
        // resize needed
    }
    else {
        assert(result == vk::Result::eSuccess);
    }
}

void VulkanRenderer::createFrameContexts() {
    VulkanCommandBuffers commandBuffers = VulkanCommandBuffers(*device, *commandPool, MAX_FRAMES_IN_FLIGHT);

    std::vector<std::unique_ptr<VulkanBuffer>> uniformBuffers;
    uniformBuffers.reserve(MAX_FRAMES_IN_FLIGHT);
    for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        uniformBuffers.emplace_back(createVulkanBuffer(sizeof(rhi::UniformBufferObject), rhi::BufferType::UniformBuffer));
    }

    VulkanDescriptorSets descriptorSets = VulkanDescriptorSets(*device, *descriptorSetLayout,*descriptorPool, uniformBuffers, MAX_FRAMES_IN_FLIGHT);
    frameContexts.reserve(MAX_FRAMES_IN_FLIGHT);
    for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        VulkanFrameContext frameContext{
            .pipeline = *pipeline,
            .commandBuffer = std::move(commandBuffers.getHandle()[i]),
            .descriptorSet = std::move(descriptorSets.getHandle()[i]),
            .uniformBuffer = std::move(uniformBuffers[i]),
            .presentCompleteSemaphore =vk::raii::Semaphore(device->getDevice(), vk::SemaphoreCreateInfo()),
            .inFlightFence = vk::raii::Fence(device->getDevice(), vk::FenceCreateInfo{
                vk::FenceCreateInfo{ .flags = vk::FenceCreateFlagBits::eSignaled }})
        };
        frameContexts.emplace_back(std::move(frameContext));
    }
}

}
