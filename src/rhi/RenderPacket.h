//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once

#include "../utils/IDSystem.h"

namespace obsidium {

class AssetManager;
class Camera;

}

namespace obsidium::rhi {

struct CameraTransform {
    glm::mat4 view{};
    Camera* camera = nullptr;
};

struct Renderable {
    AssetID meshID = InvalidAssetID;
    AssetID textureID = InvalidAssetID;
    glm::mat4 model{};
};

struct RenderPacket {
    std::vector<Renderable> renderables;
    CameraTransform cameraTransform;
    AssetManager* assetManager = nullptr;
};

}
