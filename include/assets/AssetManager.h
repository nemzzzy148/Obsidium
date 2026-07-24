//
// Created by Nemesis Verstraete on 24/07/2026.
//

#pragma once
#include <memory>

#include "MeshManager.h"
#include "TextureManager.h"

namespace obsidium {

class AssetManager {
public:
    explicit AssetManager(Renderer* renderer);

    [[nodiscard]] MeshManager& getMeshManager() const { return *meshManager; }
    [[nodiscard]] TextureManager& getTextureManager() const { return *textureManager; }

    // meshManager
    [[nodiscard]] AssetID addMesh(const Mesh& data) const;
    void removeMesh(AssetID id) const;

    [[nodiscard]] GPUMesh getMesh(AssetID id) const;

    [[nodiscard]] rhi::Buffer* getVertexBuffer() const;
    [[nodiscard]] rhi::Buffer* getIndexBuffer() const;

private:
    Renderer* renderer = nullptr;
    std::unique_ptr<IDSystem<AssetID>> idSystem;
    std::unique_ptr<MeshManager> meshManager;
    std::unique_ptr<TextureManager> textureManager;
};

}
