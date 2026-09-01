//
// Created by Nemesis Verstraete on 18/07/2026.
//
#pragma once

#include <memory>

#include "../../src/utils/IDSystem.h"
#include "../graphics/Texture.h"

namespace obsidium {

struct SamplerState;

class Renderer;

class TextureManager {
public:
    TextureManager(Renderer* renderer, IDSystem<AssetID>* idSystem);

    AssetID add(Texture texture);
    AssetID add(const Image& image, SamplerState samplerState);

    void remove(AssetID id);

    Texture* getTexture(AssetID id);
private:

    std::unordered_map<AssetID, Texture> textures;
    std::unordered_map<uint64_t, AssetID> hashes;

    Renderer* renderer = nullptr;
    IDSystem<AssetID>* idSystem = nullptr;

    friend class AssetManager;
};

}
