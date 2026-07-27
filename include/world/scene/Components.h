//
// Created by Nemesis Verstraete on 16/07/2026.
//
#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Camera.h"
#include "graphics/Texture.h"
#include "../../../src/utils/IDSystem.h"

namespace obsidium {

enum class Components {
    Tag,
    Transform,
    Mesh,
    Material,
    Camera,
    Pointer
};

struct Component {
    bool enabled = true;
};

struct EntityComponent : Component {
    std::string name;
    uint32_t sceneIndex;

    // keep in transitioning scene
    bool destroyOnLoad = false;
};

struct TagComponent : Component {
    std::string tag;
};

struct TransformComponent {
    glm::vec3 position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

    [[nodiscard]] glm::mat4 getModelMatrix() const {
        return  glm::translate(glm::mat4(1.0f), position) *
            glm::mat4_cast(glm::quat(glm::radians(rotation))) *
                glm::scale(glm::mat4(1.0f), scale);
    }
};

struct MeshComponent : Component {
    AssetID id = InvalidAssetID;
};

struct MaterialComponent : Component {
    AssetID textureID = InvalidAssetID;
    AssetID shaderID = InvalidAssetID;
};

struct CameraComponent : Component {
    Camera camera;
};

struct PointerComponent : Component {
    void* pointer = nullptr;
};

template<Components C> struct ComponentMapping;

template<> struct ComponentMapping<Components::Tag> { using type = TagComponent; };
template<> struct ComponentMapping<Components::Transform> { using type = TransformComponent; };
template<> struct ComponentMapping<Components::Mesh> { using type = MeshComponent; };
template<> struct ComponentMapping<Components::Material> { using type = MaterialComponent; };
template<> struct ComponentMapping<Components::Camera> { using type = CameraComponent; };
template<> struct ComponentMapping<Components::Pointer> { using type = PointerComponent; };

template<Components C> using ComponentType = ComponentMapping<C>::type;

}