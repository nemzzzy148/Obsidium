//
// Created by Nemesis Verstraete on 19/07/2026.
//

#include "../../include/assets/TextureManager.h"

#include <algorithm>

#include "../utils/Logger.h"
#include "graphics/Renderer.h"
#include "graphics/Sampler.h"

namespace obsidium {
TextureManager::TextureManager(Renderer *renderer, IDSystem<AssetID>* idSystem) : renderer(renderer), idSystem(idSystem)  {}

AssetID TextureManager::add(Texture texture) {
    const auto it = std::ranges::find_if(textures, [&](const auto& text) {
        return (text.second.getHash() == texture.getHash()) &&
            (text.second.getHeight() == texture.getHeight()) && (text.second.getWidth() == texture.getWidth());
    });
    if (it != textures.end()) {
        LOG_INFO("found matching texture, returning match.");
        return it->first;
    };

    AssetID id = idSystem->allocate();
    textures.emplace(id, std::move(texture));
    return id;
}

AssetID TextureManager::add(const Image &image, const SamplerState samplerState) {
    if (!image.getData() || image.getWidth() < 1 || image.getHeight() < 1) {
        LOG_ERROR("invalid image provided, returning invalid asset id.");
        return InvalidAssetID;
    }
    return add(renderer->createTexture(image, samplerState));
}

void TextureManager::remove(const AssetID id) {
    if (id == InvalidAssetID || !textures.contains(id)) {
        LOG_WARNING("failed to remove texture because of invalid asset id.");
        return;
    }
    idSystem->free(id);
    textures.erase(id);
}

Texture* TextureManager::getTexture(const AssetID id) {
    if (id == InvalidAssetID || !textures.contains(id)) {
        LOG_ERROR("failed to get texture because of invalid asset id, returning nullptr!");
        return nullptr;
    }
    return &textures.at(id);
}

}
