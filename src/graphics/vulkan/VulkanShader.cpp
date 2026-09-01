//
// Created by Nemesis Verstraete on 05/08/2026.
//

#include "VulkanShader.h"

namespace obsidium {

VulkanShader::VulkanShader(std::unique_ptr<vulkan::VulkanPipelineLayout> pipelineLayout,
    std::unique_ptr<vulkan::VulkanPipeline> pipeline, vk::raii::ShaderModule shaderModule) :
    pipelineLayout(std::move(pipelineLayout)), pipeline(std::move(pipeline)),
    shaderModule(std::move(shaderModule)) {}

}
