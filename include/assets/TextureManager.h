//
// Created by Nemesis Verstraete on 18/07/2026.
//
#pragma once

#include <memory>

#include "../../src/utils/IDSystem.h"
#include "../graphics/Texture.h"

namespace obsidium {

class Renderer;

class TextureManager {
public:
    AssetID add(Texture texture);
    AssetID add(const Image& image);

    void remove(AssetID id);

    Texture* getTexture(AssetID id);
private:
    TextureManager() = default;
    static std::unique_ptr<TextureManager> create(Renderer* renderer, IDSystem<AssetID>* idSystem);

    std::unordered_map<AssetID, Texture> textures;

    Renderer* renderer = nullptr;
    IDSystem<AssetID>* idSystem = nullptr;

    friend class AssetManager;
};

}
