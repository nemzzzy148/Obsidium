//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "../../include/assets/MeshManager.h"

#include <iostream>

#include "../../include/utils/Hash.h"

namespace obsidium {

AssetID MeshManager::add(const Mesh &data) {
    if (data.vertices.empty() || data.indices.empty()) return InvalidAssetID;

    const size_t vertexSize = data.vertices.size() * sizeof(Vertex);
    const size_t indexSize = data.indices.size() * sizeof(Index);
    uint64_t hash = hash::fnv1a(data.vertices.data(), vertexSize);
    hash = hash::fnv1aContinue(hash, data.indices.data(), indexSize);

    auto it = hashes.find(hash);
    if (it != hashes.end()) {
        const AssetID collision = it->second;
        const GPUMesh collidedMesh = meshes.at(collision);

        if (collidedMesh.indexCount == data.indices.size() &&
            collidedMesh.vertexCount == data.vertices.size()) {
            return  collision;
        }
    }


    bool foundVertexRegion = false;
    BufferRegion vertexRegion;
    BufferRegion newVertexSpace;
    size_t freeVertex = std::numeric_limits<size_t>::max();

    for (size_t i = 0; i < freeVertexSpaces.size(); i++) {
        if (freeVertexSpaces[i].size >= vertexSize) {
            foundVertexRegion = true;
            freeVertex = i;

            vertexRegion.offset = freeVertexSpaces[i].offset;
            vertexRegion.size = vertexSize;

            newVertexSpace.size = freeVertexSpaces[i].size - vertexSize;
            newVertexSpace.offset = freeVertexSpaces[i].offset + vertexSize;
            break;
        }
    }

    bool foundIndexRegion = false;
    BufferRegion indexRegion;
    BufferRegion newIndexSpace;
    size_t freeIndex = std::numeric_limits<size_t>::max();

    for (size_t i = 0; i < freeIndexSpaces.size(); i++) {
        if (freeIndexSpaces[i].size >= indexSize) {
            foundIndexRegion = true;
            freeIndex = i;

            indexRegion.offset = freeIndexSpaces[i].offset;
            indexRegion.size = indexSize;

            newIndexSpace.size = freeIndexSpaces[i].size - indexSize;
            newIndexSpace.offset = freeIndexSpaces[i].offset + indexSize;
            break;
        }
    }

    if (foundVertexRegion && foundIndexRegion) {
        freeVertexSpaces.erase(freeVertexSpaces.begin() + freeVertex);
        freeIndexSpaces.erase(freeIndexSpaces.begin() + freeIndex);

        if (newVertexSpace.size > 0) {
            freeVertexSpaces.push_back(newVertexSpace);
        }
        if (newIndexSpace.size > 0) {
            freeIndexSpaces.push_back(newIndexSpace);
        }

        GPUMesh mesh{
            .vertexRegion = vertexRegion,
            .indexRegion = indexRegion,
            .vertexCount = static_cast<uint32_t>(data.vertices.size()),
            .indexCount = static_cast<uint32_t>(data.indices.size()),
            .hash = hash
        };

        vertexBuffer->write(data.vertices.data(), vertexRegion.size, vertexRegion.offset);
        indexBuffer->write(data.indices.data(), indexRegion.size, indexRegion.offset);

        AssetID id = idSystem->allocate();

        hashes.emplace(hash, id);
        meshes.emplace(id, mesh);

        return id;
    }

    std::cerr << "no memory available in the buffers to allocate data for the mesh" << std::endl;

    return InvalidAssetID;
}

static void coalesceAndFree(std::vector<BufferRegion>& freeSpace, BufferRegion region) {
    bool merged = true;
    while (merged) {
        merged = false;
        for (size_t i = 0; i < freeSpace.size(); i++) {
            const BufferRegion space = freeSpace[i];
            bool leftAdjacent  = (space.size + space.offset) == region.offset;
            bool rightAdjacent = (region.size + region.offset) == space.offset;
            if (leftAdjacent || rightAdjacent) {
                if (leftAdjacent) region.offset = space.offset;
                region.size += space.size;

                freeSpace.erase(freeSpace.begin() + i);
                merged = true;
                break;
            }
        }
    }
    freeSpace.push_back(region);
}

void MeshManager::remove(const AssetID id) {
    if (!meshes.contains(id)) {
        std::cerr << "the mesh handle " << id.index << ":" << id.version << " is invalid" << std::endl;
        return;
    }

    const GPUMesh mesh = meshes.at(id);
    meshes.erase(id);
    hashes.erase(mesh.hash);
    idSystem->free(id);

    coalesceAndFree(freeVertexSpaces, mesh.vertexRegion);
    coalesceAndFree(freeIndexSpaces, mesh.indexRegion);
}

GPUMesh MeshManager::getMesh(const AssetID id) const {
    return meshes.at(id);
}

std::unique_ptr<MeshManager> MeshManager::create(const Renderer& renderer, IDSystem<AssetID>* idSystem) {
    auto assetManager = std::unique_ptr<MeshManager>(new MeshManager());
    assetManager->vertexBuffer = std::move(renderer.getBackend()->createBuffer(vertexAllocationBufferSize, BufferType::IndexBuffer));
    assetManager->indexBuffer = std::move(renderer.getBackend()->createBuffer(indexAllocationBufferSize, BufferType::IndexBuffer));
    assetManager->idSystem = idSystem;

    assetManager->freeVertexSpaces.push_back({vertexAllocationBufferSize, 0});
    assetManager->freeIndexSpaces.push_back({indexAllocationBufferSize, 0});
    return std::move(assetManager);
}

}
