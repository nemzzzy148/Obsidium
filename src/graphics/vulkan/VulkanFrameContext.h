//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include "VulkanPipeline.h"
#include "../../rhi/RenderPacket.h"

namespace obsidium::vulkan {

struct VulkanFrameContext {
    VulkanPipeline& pipeline;
    vk::raii::CommandBuffer commandBuffer;

    vk::raii::DescriptorSet descriptorSet;
    std::unique_ptr<VulkanBuffer> uniformBuffer;

    vk::raii::Semaphore presentCompleteSemaphore;
    vk::raii::Fence inFlightFence;
};

}
