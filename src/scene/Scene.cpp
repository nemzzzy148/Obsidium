//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "../../include/scene/Scene.h"

namespace obsidium {

std::unique_ptr<Scene> Scene::create(MeshManager *meshManager, uint32_t sceneIndex) {
    std::unique_ptr<Scene> scene = std::unique_ptr<Scene>(new Scene());
    scene->meshManager = meshManager;
    scene->sceneIndex = sceneIndex;

    scene->cameraObject = scene->createGameObject();
    scene->setCamera(scene->cameraObject, Camera());

    return std::move(scene);
}

GameObject Scene::createGameObject() {
    UUID_t uuid = UUID::generateUUID();
    GameObject gameObject = GameObject(this, uuid);
    gameObjects.insert({ uuid, gameObject});
    transformComponents[uuid] = TransformComponent{};

    return gameObject;
}

void Scene::removeGameObject(const GameObject& gameObject) {
    if (cameraObject == gameObject) return;

    gameObjects.erase(gameObject.handle);
    removeTag(gameObject);
    removeCamera(gameObject);
    removeMesh(gameObject);
    removePointer(gameObject);
}

bool Scene::isGameObjectPresent(const GameObject &gameObject) const {
    return gameObjects.contains(gameObject.handle);
}

void Scene::setTransform(const GameObject &gameObject, const TransformComponent &newTransform) {
    if (const auto it = transformComponents.find(gameObject.handle); it != transformComponents.end()) {
        it->second = newTransform;
    }
}

TransformComponent Scene::getTransform(const GameObject &gameObject) const {
    if (const auto it = transformComponents.find(gameObject.handle); it != transformComponents.end()) {
        return it->second;
    }
    return {};
}

void Scene::setPosition(const GameObject &gameObject, const glm::vec3& position) {
    if (const auto it = transformComponents.find(gameObject.handle); it != transformComponents.end()) {
        it->second.position = position;
    }
}

glm::vec3 Scene::getPosition(const GameObject &gameObject) const {
    if (const auto it = transformComponents.find(gameObject.handle); it != transformComponents.end()) {
        return it->second.position;
    }
    return {};
}

void Scene::setRotation(const GameObject &gameObject, const glm::vec3& rotation) {
    if (const auto it = transformComponents.find(gameObject.handle); it != transformComponents.end()) {
        it->second.rotation = rotation;
    }
}

glm::vec3 Scene::getRotation(const GameObject &gameObject) const {
    if (const auto it = transformComponents.find(gameObject.handle); it != transformComponents.end()) {
        return it->second.rotation;
    }
    return {};
}

void Scene::setScale(const GameObject &gameObject, const glm::vec3& scale) {
    if (const auto it = transformComponents.find(gameObject.handle); it != transformComponents.end()) {
        it->second.scale = scale;
    }
}

glm::vec3 Scene::getScale(const GameObject &gameObject) const {
    if (const auto it = transformComponents.find(gameObject.handle); it != transformComponents.end()) {
        return it->second.scale;
    }
    return { 1.0f, 1.0f, 1.0f };
}

GameObject Scene::getGameObjectWithTag(const std::string &tag) const {
    const auto it = std::ranges::find_if(tagComponents, [&](const auto& t) {
        return t.second.tag == tag;
    });

    if (it != tagComponents.end()) {
        return gameObjects.at(it->first);
    }

    return {};
}

void Scene::setTag(const GameObject &gameObject, const std::string &tag) {

}

std::string Scene::getTag(const GameObject &gameObject) const {
    return {};
}

void Scene::removeTag(const GameObject &gameObject) {
}

bool Scene::hasTag(const GameObject &gameObject) const {
    return tagComponents.contains(gameObject.handle);
}

void Scene::setMesh(const GameObject &gameObject, Mesh &data) {
    if (!gameObjects.contains(gameObject.handle)) return;
    meshComponents[gameObject.handle].handle = meshManager->add(data);
}

void Scene::setMesh(const GameObject &gameObject, Shape &shape) {
}

void Scene::setMesh(const GameObject &gameObject, MeshHandle mesh) {
    if (!gameObjects.contains(gameObject.handle)) return;
    meshComponents[gameObject.handle].handle = mesh;
}

MeshHandle Scene::getMesh(const GameObject &gameObject) const {
    return 0;
}

void Scene::removeMesh(const GameObject &gameObject) {
}

bool Scene::hasMesh(const GameObject &gameObject) const {
    return false;
}

void Scene::setCamera(const GameObject &gameObject, Camera camera) {
    if (gameObjects.contains(gameObject.handle)) {
        cameraComponents[gameObject.handle] = CameraComponent{ .camera = camera };
    }

}

const Camera *Scene::getCamera(const GameObject &gameObject) const {
    if (const auto it = cameraComponents.find(gameObject.handle); it != cameraComponents.end()) {
        return &it->second.camera;
    }
    return nullptr;
}

void Scene::removeCamera(const GameObject &gameObject) {
    if (cameraObject.handle != gameObject.handle) {
        cameraComponents.erase(gameObject.handle);
    }
}

bool Scene::hasCamera(const GameObject &gameObject) const {
    return cameraComponents.contains(gameObject.handle);
}

void Scene::setPointer(const GameObject &gameObject, void *pointer) {
}

void * Scene::getPointer(const GameObject &gameObject) const {
}

void Scene::removePointer(const GameObject &gameObject) {
    if (!gameObjects.contains(gameObject.handle)) return;

}

bool Scene::hasPointer(const GameObject &gameObject) const {
     return pointerComponents.contains(gameObject.handle);
}

void Scene::setMainCamera(const GameObject &gameObject) {
    if (gameObjects.contains(gameObject.handle)) {
        cameraObject = gameObject;
    }
}

GameObject Scene::getMainCamera() const {
    return cameraObject;
}

rhi::RenderPacket Scene::createRenderPacket() {
    rhi::RenderPacket renderPacket;
    for (auto &[handle , mesh] : meshComponents) {
        renderPacket.meshes.emplace(mesh.handle, transformComponents.at(handle).getModelMatrix());
    }

    renderPacket.camera = std::make_pair(&cameraComponents.at(cameraObject.handle).camera,
        glm::inverse(transformComponents.at(cameraObject.handle).getModelMatrix()));

    return std::move(renderPacket);
}

}
