//
// Created by Nemesis Verstraete on 06/08/2026.
//

#pragma once
#include "VulkanTexture.h"
#include "../../rhi/RenderTarget.h"

namespace obsidium::vulkan {

class VulkanRenderTarget : public rhi::RenderTarget {

private:
    VulkanTexture* texture = nullptr;
    bool isSwapChain = false;
};

}
