//
// Created by Nemesis Verstraete on 05/08/2026.
//

#pragma once
#include "VulkanPipeline.h"
#include "../../rhi/Shader.h"

namespace obsidium {

class VulkanShader : public rhi::Shader {
public:
    VulkanShader(std::unique_ptr<vulkan::VulkanPipelineLayout> pipelineLayout,
        std::unique_ptr<vulkan::VulkanPipeline> pipeline, vk::raii::ShaderModule shaderModule);

    [[nodiscard]] vulkan::VulkanPipeline& getPipeline() const { return *pipeline; }
private:
    std::unique_ptr<vulkan::VulkanPipelineLayout> pipelineLayout;
    std::unique_ptr<vulkan::VulkanPipeline> pipeline;
    vk::raii::ShaderModule shaderModule = nullptr;
};

}
