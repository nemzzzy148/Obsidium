//
// Created by Nemesis Verstraete on 19/07/2026.
//

#include "../../include/assets/TextureManager.h"

#include "graphics/Renderer.h"

namespace obsidium {

std::unique_ptr<TextureManager> TextureManager::create(Renderer* renderer, IDSystem<AssetID>* idSystem) {
    auto textureManager = std::unique_ptr<TextureManager>(new TextureManager());
    textureManager->idSystem = idSystem;
    textureManager->renderer = renderer;
    return std::move(textureManager);
}

AssetID TextureManager::add(Texture texture) {
    const auto it = std::ranges::find_if(textures, [&](const auto& text) {
        return (text.second.getHash() == texture.getHash()) &&
            (text.second.getHeight() == texture.getHeight()) && (text.second.getWidth() == texture.getWidth());
    });
    if (it != textures.end()) return it->first;

    AssetID id = idSystem->allocate();
    textures.emplace(id, std::move(texture));
    return id;
}

AssetID TextureManager::add(const Image &image) {
    return add(renderer->createTexture(image));
}

void TextureManager::remove(const AssetID id) {
    idSystem->free(id);
    textures.erase(id);
}

Texture* TextureManager::getTexture(const AssetID id) {
    return &textures.at(id);
}

}
