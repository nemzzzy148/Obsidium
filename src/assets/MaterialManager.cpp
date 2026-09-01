//
// Created by Nemesis Verstraete on 03/08/2026.
//

#include "../../include/assets/MaterialManager.h"

#include "graphics/Material.h"

namespace obsidium {

MaterialManager::MaterialManager(Renderer *renderer, IDSystem<AssetID>* idSystem) {
    textureManager = std::make_unique<TextureManager>(renderer, idSystem);
    shaderManage = std::make_unique<ShaderManager>(renderer, idSystem);
}

AssetID MaterialManager::add(Material material) {

}

Material * MaterialManager::getMaterial(AssetID id) {
}

}
