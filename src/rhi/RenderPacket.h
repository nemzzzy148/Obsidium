//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include "../../include/graphics/Mesh.h"
#include "../../include/scene/Camera.h"

namespace obsidium::rhi {

struct RenderPacket {
    std::unordered_map<MeshHandle, glm::mat4> meshes;
    std::pair<const Camera*, glm::mat4x4> camera;
};

}
