#include <Obsidium.h>

#include "../src/rhi/Fragment.h"
#include "../src/rhi/Instance.h"
#include "../src/rhi/Vertex.h"
#include "graphics/Buffer.h"
#include "../src/rhi/Pipeline.h"

int main() {
    const auto window = obsidium::Window::create();
    auto instance = obsidium::rhi::Instance({});
    auto surface = window.getSurface(instance);

    const obsidium::rhi::SurfaceConfiguration configuration{
        .width = window.getWidth(),
        .height = window.getHeight()
    };
    surface.configure(configuration);

    const obsidium::rhi::DeviceSelectorCreateInfo selectorInfo {
        .compatibleSurface = &surface
    };
    obsidium::rhi::DeviceSelector* selector = instance.createDeviceSelector(selectorInfo);
    obsidium::rhi::Device device = selector->createDevice();
    obsidium::rhi::Queue queue = device.getQueue();

    // pipeline

    constexpr obsidium::rhi::ShaderCreateInfo shaderInfo {
        .code = "which"
    };

    obsidium::rhi::Shader* shader = device.createShader(shaderInfo);

    obsidium::rhi::VertexState vertexState {
        .shader = shader
    };

    obsidium::rhi::FragmentState fragmentState {
        .shader = shader
    };

    obsidium::rhi::RenderPipelineCreateInfo renderPipelineInfo {
        .vertexState = vertexState,
        .fragmentState = fragmentState
    };

    obsidium::rhi::RenderPipeline* renderPipeline = device.createRenderPipeline(renderPipelineInfo);
}