//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "../../../include/world/scene/Scene.h"

#include <ranges>

namespace obsidium {

std::unique_ptr<Scene> Scene::create(MeshManager *meshManager, uint32_t sceneIndex) {
    std::unique_ptr<Scene> scene = std::unique_ptr<Scene>(new Scene());
    scene->meshManager = meshManager;
    scene->sceneIndex = sceneIndex;

    scene->cameraObject = scene->createEntity();
    scene->setCamera(scene->cameraObject, Camera());

    return std::move(scene);
}

Entity Scene::createEntity() {
    UUID_t uuid = UUID::generateUUID();
    Entity Entity = Entity(this, uuid);
    Entitys.insert({ uuid, Entity});
    transformComponents[uuid] = TransformComponent{};

    return Entity;
}

void Scene::removeEntity(const Entity& Entity) {
    if (cameraObject == Entity) return;

    entities.erase(Entity.handle);
    removeTag(Entity);
    removeCamera(Entity);
    removeMesh(Entity);
    removePointer(Entity);
}

bool Scene::isEntityPresent(const Entity &Entity) const {
    return entities.contains(Entity.handle);
}

void Scene::setTransform(const Entity &Entity, const TransformComponent &newTransform) {
    if (const auto it = transformComponents.find(Entity.handle); it != transformComponents.end()) {
        it->second = newTransform;
    }
}

TransformComponent Scene::getTransform(const Entity &Entity) const {
    if (const auto it = transformComponents.find(Entity.handle); it != transformComponents.end()) {
        return it->second;
    }
    return {};
}

void Scene::setPosition(const Entity &Entity, const glm::vec3& position) {
    if (const auto it = transformComponents.find(Entity.handle); it != transformComponents.end()) {
        it->second.position = position;
    }
}

glm::vec3 Scene::getPosition(const Entity &Entity) const {
    if (const auto it = transformComponents.find(Entity.handle); it != transformComponents.end()) {
        return it->second.position;
    }
    return {};
}

void Scene::setRotation(const Entity &Entity, const glm::vec3& rotation) {
    if (const auto it = transformComponents.find(Entity.handle); it != transformComponents.end()) {
        it->second.rotation = rotation;
    }
}

glm::vec3 Scene::getRotation(const Entity &Entity) const {
    if (const auto it = transformComponents.find(Entity.handle); it != transformComponents.end()) {
        return it->second.rotation;
    }
    return {};
}

void Scene::setScale(const Entity &Entity, const glm::vec3& scale) {
    if (const auto it = transformComponents.find(Entity.handle); it != transformComponents.end()) {
        it->second.scale = scale;
    }
}

glm::vec3 Scene::getScale(const Entity &Entity) const {
    if (const auto it = transformComponents.find(Entity.handle); it != transformComponents.end()) {
        return it->second.scale;
    }
    return { 1.0f, 1.0f, 1.0f };
}

Entity Scene::getEntityWithTag(const std::string &tag) const {
    const auto it = std::ranges::find_if(tagComponents, [&](const auto& t) {
        return t.second.tag == tag;
    });
    return (it != tagComponents.end()) ? Entitys.at(it->first) : Entity{};
}

void Scene::setTag(const Entity &Entity, const std::string &tag) {
    if (Entity.scene != this) return;
    tagComponents[Entity.handle].tag = tag;
}

std::string Scene::getTag(const Entity &Entity) const {
    if (Entity.scene != this) return "";
    const auto it = std::ranges::find_if(tagComponents, [&](const auto& tag) {
        return tag.first == Entity.handle;
    });
    return (it != tagComponents.end()) ? it->second.tag : "";
}

void Scene::removeTag(const Entity &Entity) {
    if (Entity.scene != this) return;
    tagComponents.erase(Entity.handle);
}

bool Scene::hasTag(const Entity &Entity) const {
    return tagComponents.contains(Entity.handle);
}

void Scene::setMesh(const Entity &Entity, Mesh &data) {
    if (!Entitys.contains(Entity.handle)) return;
    meshComponents[Entity.handle].meshHandle = meshManager->add(data);
}

void Scene::setMesh(const Entity &Entity, const MeshHandle mesh) {
    if (!Entitys.contains(Entity.handle)) return;
    meshComponents[Entity.handle].meshHandle = mesh;
}

MeshHandle Scene::getMesh(const Entity &Entity) const {
    if (Entity.scene != this) return InvalidMeshHandle;
    const auto it = std::ranges::find_if(meshComponents, [&](const auto& mesh) {
        return mesh.first == Entity.handle;
    });
    return (it != meshComponents.end()) ? it->second.meshHandle
}

void Scene::removeMesh(const Entity &Entity) {
    if (Entity.scene != this) meshComponents.erase(Entity.handle);
}

bool Scene::hasMesh(const Entity &Entity) const {
    return (Entity.scene == this && meshComponents.contains(Entity.handle));
}

void Scene::setMaterial(const Entity &Entity, Image &image) {
    if (Entity.scene != this) return;
}

void Scene::setMaterial(const Entity &Entity, TextureHandle textureHandle) {
}

TextureHandle Scene::getMaterial(const Entity &Entity) const {
}

void Scene::removeMaterial(const Entity &Entity) const {
}

bool Scene::hasMaterial(const Entity &Entity) const {
}

void Scene::setCamera(const Entity &Entity, const Camera &camera) {
    if (Entitys.contains(Entity.handle)) {
        cameraComponents[Entity.handle] = CameraComponent{ .camera = camera };
    }
}

const Camera *Scene::getCamera(const Entity &Entity) const {
    if (const auto it = cameraComponents.find(Entity.handle); it != cameraComponents.end()) {
        return &it->second.camera;
    }
    return nullptr;
}

void Scene::removeCamera(const Entity &Entity) {
    if (cameraObject.handle == Entity.handle) return;
    cameraComponents.erase(Entity.handle);
}

bool Scene::hasCamera(const Entity &Entity) const {
    return cameraComponents.contains(Entity.handle);
}

void Scene::setPointer(const Entity &Entity, void *pointer) {
    if (!Entitys.contains(Entity.handle)) return;
    pointerComponents[Entity.handle].pointer = pointer;
}

void * Scene::getPointer(const Entity &Entity) const {
    if (!Entitys.contains(Entity.handle) || !pointerComponents.contains(Entity.handle)) return nullptr;
    return pointerComponents.at(Entity.handle).pointer;
}

void Scene::removePointer(const Entity &Entity) {
    if (!Entitys.contains(Entity.handle)) return;
    pointerComponents.erase(Entity.handle);
}

bool Scene::hasPointer(const Entity &Entity) const {
     return pointerComponents.contains(Entity.handle);
}

void Scene::setMainCamera(const Entity &Entity) {
    if (Entitys.contains(Entity.handle)) {
        cameraObject = Entity;
    }
}

Entity Scene::getMainCamera() const {
    return cameraObject;
}

rhi::RenderPacket Scene::createRenderPacket() {
    rhi::RenderPacket renderPacket;
    for (const auto &[handle, mesh] : meshComponents) {
        renderPacket.meshes.emplace_back(mesh.meshHandle, mesh.textureHandle, transformComponents.at(handle).getModelMatrix());
    }

    renderPacket.camera = std::make_pair(&cameraComponents.at(cameraObject.handle).camera,
        glm::inverse(transformComponents.at(cameraObject.handle).getModelMatrix()));

    return std::move(renderPacket);
}

}
