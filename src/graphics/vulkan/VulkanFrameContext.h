//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include "VulkanPipeline.h"
#include "../../rhi/RenderPacket.h"

namespace obsidium::vulkan {

struct VulkanFrameContext {
    vk::raii::CommandBuffer commandBuffer;

    vk::raii::Semaphore presentCompleteSemaphore;
    vk::raii::Fence inFlightFence;
};

}
