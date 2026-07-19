//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <vector>

#include "Mesh.h"
#include "Renderer.h"
#include "../../src/rhi/Buffer.h"

namespace obsidium {

class Renderer;

class MeshManager {
public:
    MeshHandle add(const Mesh& data);
    void remove(MeshHandle handle);

    [[nodiscard]] GPUMesh getMesh(MeshHandle handle) const;

    [[nodiscard]] rhi::Buffer* getVertexBuffer() const { return vertexBuffer.get(); }
    [[nodiscard]] rhi::Buffer* getIndexBuffer() const { return indexBuffer.get(); }
private:
    MeshManager() = default;
    static std::unique_ptr<MeshManager> create(const Renderer& renderer);

    static constexpr size_t vertexAllocationBufferSize = 4194304; //2^22
    static constexpr size_t indexAllocationBufferSize = 4194304;

    std::unordered_map<MeshHandle, GPUMesh> meshes;
    std::unordered_map<uint64_t, MeshHandle> hashes;
    MeshHandle currentIndex = 0;

    std::vector<BufferRegion> freeVertexSpaces;
    std::vector<BufferRegion> freeIndexSpaces;

    std::unique_ptr<rhi::Buffer> vertexBuffer;
    std::unique_ptr<rhi::Buffer> indexBuffer;

    friend class Engine;
    friend class VulkanRenderer;
};

}
