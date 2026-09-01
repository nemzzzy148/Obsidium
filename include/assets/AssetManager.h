//
// Created by Nemesis Verstraete on 24/07/2026.
//

#pragma once
#include <memory>

#include "../../src/utils/IDSystem.h"
#include "graphics/Buffer.h"
#include "graphics/Mesh.h"

namespace obsidium {
class MaterialManager;
class MeshManager;
class Renderer;

class AssetManager {
public:
    explicit AssetManager(Renderer* renderer);

    [[nodiscard]] MeshManager& getMeshManager() const { return *meshManager; }
    [[nodiscard]] MaterialManager& getTextureManager() const { return *materialManager; }

    // meshManager
    [[nodiscard]] AssetID addMesh(const Mesh& data) const;
    void removeMesh(AssetID id) const;

    [[nodiscard]] GPUMesh getMesh(AssetID id) const;

    [[nodiscard]] Buffer* getVertexBuffer() const;
    [[nodiscard]] Buffer* getIndexBuffer() const;

    // material manager

private:
    Renderer* renderer = nullptr;
    std::unique_ptr<IDSystem<AssetID>> idSystem;
    std::unique_ptr<MeshManager> meshManager;
    std::unique_ptr<MaterialManager> materialManager;
};

}
