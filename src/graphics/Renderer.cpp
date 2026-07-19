//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include <utility>

#include "../../include/graphics/Renderer.h"

#include <ranges>

#include "../rhi/RendererBackend.h"
#include "../rhi/RenderPacket.h"
#include "vulkan/VulkanRenderer.h"

namespace obsidium {

std::unique_ptr<Renderer> Renderer::create(Window* window, MeshManager* assetManager, const Backend backend) {
    auto r = std::unique_ptr<Renderer>(new Renderer());
    switch (backend) {
        case Backend::Vulkan:
            r->backend = std::make_unique<vulkan::VulkanRenderer>(window, assetManager);
            ShaderInstance::initialize(ShaderFormat::SPIRV);
    }
    r->backendType = backend;
    return std::move(r);
}

void Renderer::renderScene(Scene &scene) const {
    rhi::RenderPacket renderPacket;
    renderPacket.meshes.reserve(scene.meshComponents.size());
    const TransformComponent view = scene.getTransform(scene.getMainCamera());
    renderPacket.camera = std::make_pair( scene.getCamera(scene.getMainCamera()), Camera::getViewMat(view.position, view.rotation) );

    for (const auto &gameObject: scene.gameObjects | std::views::values) {
        if (scene.meshComponents.contains(gameObject.handle)) {
            renderPacket.meshes.emplace(scene.meshComponents.at(gameObject.handle).handle,
                scene.transformComponents.at(gameObject.handle).getModelMatrix());
        }
    }

    submitPacket(renderPacket);
}

void Renderer::resize(const uint32_t width, const uint32_t height) const {
    backend->resize(width, height);
}

void Renderer::destroy() const {
    backend->destroy();
}

void Renderer::submitPacket(rhi::RenderPacket& packet) const {
    backend->submitPacket(packet);
}

}
