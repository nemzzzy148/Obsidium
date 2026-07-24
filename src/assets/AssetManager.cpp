//
// Created by Nemesis Verstraete on 24/07/2026.
//

#include "../../include/assets/AssetManager.h"

namespace obsidium {

AssetManager::AssetManager(Renderer *renderer) {
    idSystem = std::make_unique<IDSystem<AssetID>>();
    meshManager = MeshManager::create(*renderer, idSystem.get());
    textureManager = TextureManager::create(renderer, idSystem.get());
}

AssetID AssetManager::addMesh(const Mesh &data) const {
    return meshManager->add(data);
}

void AssetManager::removeMesh(const AssetID id) const {
    meshManager->remove(id);
}

GPUMesh AssetManager::getMesh(const AssetID id) const {
    return meshManager->getMesh(id);
}

rhi::Buffer * AssetManager::getVertexBuffer() const {
    return meshManager->getVertexBuffer();
}

rhi::Buffer * AssetManager::getIndexBuffer() const {
    return meshManager->getIndexBuffer();
}

}
