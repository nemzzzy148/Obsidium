//
// Created by Nemesis Verstraete on 03/08/2026.
//

#pragma once
#include "ShaderManager.h"
#include "TextureManager.h"
#include "../../src/utils/IDSystem.h"

namespace obsidium {
class Material;

class MaterialManager {
public:
    explicit MaterialManager(Renderer* renderer, IDSystem<AssetID>* idSystem);

    AssetID add(Material material);

    Material* getMaterial(AssetID id);
private:
    std::unordered_map<AssetID, Material> materials;
    std::unordered_map<uint64_t, AssetID> hashes;

    std::unique_ptr<TextureManager> textureManager;
    std::unique_ptr<ShaderManager> shaderManage;
};

}
