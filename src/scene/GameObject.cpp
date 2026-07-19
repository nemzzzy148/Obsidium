//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "../../include/scene/GameObject.h"

#include "../../include/scene/Scene.h"

namespace obsidium {

GameObject::GameObject(Scene *scene, uint64_t handle) : scene(scene), handle(handle) {}

void GameObject::setTransform(TransformComponent transform) {
    scene->setTransform(*this, transform);
}

void GameObject::setPosition(glm::vec3 position) {
    scene->setPosition(*this, position);
}

void GameObject::setRotation(glm::vec3 rotation) {
    scene->setRotation(*this, rotation);
}

void GameObject::setScale(glm::vec3 scale) {
    scene->setScale(*this, scale);
}

bool GameObject::isValid() {
    return handle != ~0;
}

}
