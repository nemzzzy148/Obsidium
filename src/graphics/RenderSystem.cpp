//
// Created by Nemesis Verstraete on 24/07/2026.
//

#include "../../include/graphics/RenderSystem.h"
#include "../../include/world/EntityComponentManager.h"
#include "../../src/rhi/RenderPacket.h"
#include "world/World.h"

namespace obsidium {
RenderSystem::RenderSystem(Renderer &renderer) : renderer(renderer) {}

void RenderSystem::update(World &world, float dt) {
    rhi::RenderPacket renderPacket;

    for (const EntityID& id : world.sceneManager().activeSceneObjects()) {
        const MeshComponent mesh = ECM.getComponent<MeshComponent>(id);
        if (!mesh.enabled) continue;
        renderPacket.renderables.push_back({mesh.id,
            ECM.getComponent<MaterialComponent>(id).textureID,
            ECM.getComponent<TransformComponent>(id).getModelMatrix()});
    }

    renderer.submitPacket(renderPacket);
}

}
