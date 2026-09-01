//
// Created by Nemesis Verstraete on 27/07/2026.
//

#pragma once

#include <unordered_map>

#include "../../src/utils/IDSystem.h"
#include "../graphics/Renderer.h"
#include "graphics/Shader.h"

namespace obsidium {

class ShaderManager {
public:
    explicit ShaderManager(Renderer* renderer, IDSystem<AssetID>* idSystem);

    AssetID add(const std::vector<char> &userCode);
    AssetID add(const std::string& filePath);

    void remove(AssetID id);

    Shader* getShader(AssetID id);
private:
    std::unordered_map<AssetID, std::unique_ptr<Shader>> shaders;
    std::unordered_map<uint64_t, AssetID> hashes;

    Renderer* renderer = nullptr;
    IDSystem<AssetID>* idSystem = nullptr;
};

}
