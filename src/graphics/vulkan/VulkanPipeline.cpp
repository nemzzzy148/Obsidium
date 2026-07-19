//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "VulkanPipeline.h"

#include "Mesh.h"
#include "../shader/Shader.h"

namespace obsidium::vulkan {

VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(VulkanDevice& device) {
    // descriptor set layout
    vk::DescriptorSetLayoutBinding binding {
        .binding = 0,
        .descriptorType = vk::DescriptorType::eUniformBuffer,
        .descriptorCount = 1,
        .stageFlags = vk::ShaderStageFlagBits::eVertex
    };

    vk::DescriptorSetLayoutCreateInfo layoutInfo{
        .bindingCount = 1, // change if bigger
        .pBindings = &binding
    };

    descriptorSetLayout = vk::raii::DescriptorSetLayout(device.getDevice(), layoutInfo);
}

VulkanPipelineLayout::VulkanPipelineLayout(VulkanDevice& device, VulkanDescriptorSetLayout& descriptorSetLayout) {
    vk::PipelineLayoutCreateInfo pipelineLayoutInfo{
        .setLayoutCount = 1,
        .pSetLayouts = &*descriptorSetLayout.getHandle(),
        .pushConstantRangeCount = 0
    };
    pipelineLayout = vk::raii::PipelineLayout(device.getDevice(), pipelineLayoutInfo);
}

VulkanPipeline::VulkanPipeline(VulkanDevice &device, VulkanSwapChain& swapChain, VulkanPipelineLayout& pipelineLayout, std::vector<char> code) {

    // pipeline creation
    vk::ShaderModuleCreateInfo shaderCreateInfo {
        .codeSize = code.size() * sizeof(char),
        .pCode = reinterpret_cast<uint32_t const *>(code.data())
    };
    vk::raii::ShaderModule shaderModule(device.getDevice(), shaderCreateInfo);

    vk::PipelineShaderStageCreateInfo vertInfo{
        .stage = vk::ShaderStageFlagBits::eVertex,
        .module = shaderModule,
        .pName = ShaderInstance::vertexFunctionName.c_str()
    };
    vk::PipelineShaderStageCreateInfo fragInfo{
        .stage = vk::ShaderStageFlagBits::eFragment,
        .module = shaderModule,
        .pName = ShaderInstance::fragmentFunctionName.c_str()
    };
    vk::PipelineShaderStageCreateInfo shaderStages[] = {vertInfo, fragInfo};

    auto bindingDescription = VulkanVertex::vertexBindingDescription();
    auto attributeDescriptions = VulkanVertex::vertexAttributeDescriptions();
    vk::PipelineVertexInputStateCreateInfo vertexInputInfo{
        .vertexBindingDescriptionCount = 1,
        .pVertexBindingDescriptions = &bindingDescription,
        .vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size()),
        .pVertexAttributeDescriptions = attributeDescriptions.data()
    };

    vk::PipelineInputAssemblyStateCreateInfo inputAssembly{.topology = vk::PrimitiveTopology::eTriangleList};
    vk::PipelineViewportStateCreateInfo viewportState{.viewportCount = 1, .scissorCount = 1};

    vk::PipelineRasterizationStateCreateInfo rasterizer{
        .depthClampEnable = vk::False,
        .rasterizerDiscardEnable = vk::False,
        .polygonMode = vk::PolygonMode::eFill,
        .cullMode = vk::CullModeFlagBits::eBack,
        .frontFace = vk::FrontFace::eCounterClockwise,
        .depthBiasClamp = vk::False,
        .lineWidth = 1.0
    };

    vk::PipelineMultisampleStateCreateInfo multisampling{
        .rasterizationSamples = vk::SampleCountFlagBits::e1,
        .sampleShadingEnable = vk::False
    };

    vk::PipelineColorBlendAttachmentState colorBlendAttachment{
        .blendEnable = vk::False,
        .colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA
    };
    vk::PipelineColorBlendStateCreateInfo colorBlending{
        .logicOpEnable = vk::False,
        .logicOp = vk::LogicOp::eCopy,
        .attachmentCount = 1,
        .pAttachments = &colorBlendAttachment
    };

    std::vector<vk::DynamicState> dynamicStates = {vk::DynamicState::eViewport, vk::DynamicState::eScissor};
    vk::PipelineDynamicStateCreateInfo dynamicState{
        .dynamicStateCount = static_cast<uint32_t>(dynamicStates.size()),
        .pDynamicStates = dynamicStates.data()
    };


    vk::StructureChain<vk::GraphicsPipelineCreateInfo, vk::PipelineRenderingCreateInfo> pipelineCreateInfoChain = {
           {.stageCount = 2,
            .pStages = shaderStages,
            .pVertexInputState = &vertexInputInfo,
            .pInputAssemblyState = &inputAssembly,
            .pViewportState = &viewportState,
            .pRasterizationState = &rasterizer,
            .pMultisampleState = &multisampling,
            .pColorBlendState = &colorBlending,
            .pDynamicState = &dynamicState,
            .layout = pipelineLayout.getHandle(),
            .renderPass = nullptr},
            {
            .colorAttachmentCount = 1,
            .pColorAttachmentFormats = &swapChain.getFormat().format
            }
    };

    pipeline = vk::raii::Pipeline(device.getDevice(), nullptr, pipelineCreateInfoChain.get<vk::GraphicsPipelineCreateInfo>());
}

}