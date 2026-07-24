//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include "../../include/graphics/Mesh.h"
#include "assets/AssetManager.h"
#include "graphics/Texture.h"
#include "world/scene/Camera.h"

namespace obsidium::rhi {

struct Renderable {
    AssetID meshID;
    AssetID textureID;
    glm::mat4 model;
};

struct RenderPacket {
    std::vector<Renderable> renderables;
    CameraTransform cameraTransform;
    AssetManager* assetManager;
};

}
