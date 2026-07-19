//
// Created by Nemesis Verstraete on 16/07/2026.
//
#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Camera.h"
#include "../graphics/Mesh.h"

namespace obsidium {

struct IDComponent {
    uint64_t uuid;
};
struct TagComponent {
    std::string tag;
};

struct TransformComponent {
    glm::vec3 position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

    glm::mat4 getModelMatrix() const {
        return  glm::translate(glm::mat4(1.0f), position) *
            glm::mat4_cast(glm::quat(glm::radians(rotation))) *
                glm::scale(glm::mat4(1.0f), scale);
    }
};

struct MeshComponent {
    MeshHandle handle;
};

struct CameraComponent {
    Camera camera;
};

struct PointerComponent {
    void* pointer;
};

}
