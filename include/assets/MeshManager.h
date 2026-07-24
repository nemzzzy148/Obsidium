//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <vector>

#include "../../src/utils/IDSystem.h"
#include "../graphics/Mesh.h"
#include "../graphics/Renderer.h"
#include "../../src/rhi/Buffer.h"

namespace obsidium {

class Renderer;

class MeshManager {
public:
    AssetID add(const Mesh& data);
    void remove(AssetID id);

    [[nodiscard]] GPUMesh getMesh(AssetID id) const;

    [[nodiscard]] rhi::Buffer* getVertexBuffer() const { return vertexBuffer.get(); }
    [[nodiscard]] rhi::Buffer* getIndexBuffer() const { return indexBuffer.get(); }
private:
    MeshManager() = default;
    static std::unique_ptr<MeshManager> create(const Renderer& renderer, IDSystem<AssetID>* idSystem);

    static constexpr uint64_t vertexAllocationBufferSize = 8388608; // 2^23
    static constexpr uint64_t indexAllocationBufferSize = 8388608;

    std::unordered_map<AssetID, GPUMesh> meshes;
    std::unordered_map<uint64_t, AssetID> hashes;

    std::vector<BufferRegion> freeVertexSpaces;
    std::vector<BufferRegion> freeIndexSpaces;

    std::unique_ptr<rhi::Buffer> vertexBuffer;
    std::unique_ptr<rhi::Buffer> indexBuffer;

    IDSystem<AssetID>* idSystem = nullptr;

    friend class AssetManager;
};

}
