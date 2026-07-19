//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <cstdint>

#include "Components.h"

namespace obsidium {

class Scene;

class GameObject {
public:
    GameObject() = default;

    void setTransform(TransformComponent newTransform);
    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setScale(glm::vec3 scale);

    bool isValid();

    bool operator==(const GameObject& gameObject) const {
        return (gameObject.handle == handle) && (gameObject.scene == scene);
    }
private:
    GameObject(Scene* scene, uint64_t handle);

    uint64_t handle = ~0;
    Scene* scene = nullptr;

    friend class Scene;
    friend class Renderer;
};

}
