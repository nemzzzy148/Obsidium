//
// Created by Nemesis Verstraete on 27/07/2026.
//

#include "../../include/assets/ShaderManager.h"

#include <fstream>

#include "utils/Hash.h"

namespace obsidium {

ShaderManager::ShaderManager(Renderer* renderer, IDSystem<AssetID>* idSystem) : renderer(renderer), idSystem(idSystem) {}

AssetID ShaderManager::add(const std::vector<char> &userCode) {
    const uint64_t hash = hash::fnv1a(userCode.data(), userCode.size());
    if (hashes.contains(hash)) return hashes.at(hash);

    AssetID id = idSystem->allocate();
    shaders.insert({id, std::move(std::make_unique<Shader>(renderer->createShader(userCode)))});
    hashes.insert({hash, id});

    return id;
}

AssetID ShaderManager::add(const std::string &filePath) {
    if (filePath.empty()) return  InvalidAssetID;
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return InvalidAssetID;
    const std::streamsize size = file.tellg();
    std::vector<char> buffer(size);
    file.seekg(0, std::ios::beg);
    file.read(buffer.data(), size);
    file.close();
    return add(buffer);
}

void ShaderManager::remove(const AssetID id) {
    if (!idSystem->valid(id)) return;
    idSystem->free(id);
    shaders.erase(id);
}

Shader * ShaderManager::getShader(AssetID id) {
}

}
