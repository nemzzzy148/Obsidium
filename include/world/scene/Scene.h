//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <memory>

#include "Components.h"
#include "Entity.h"
#include "../../assets/MeshManager.h"

namespace obsidium {
class Shape;

class Scene {
public:
    Scene();
    Entity createGameObject();
    void removeGameObject(const Entity& gameObject);

    [[nodiscard]] bool isGameObjectPresent(const Entity& gameObject) const;

    void setTransform(const Entity& gameObject, const TransformComponent &newTransform);
    [[nodiscard]] TransformComponent getTransform(const Entity& gameObject) const;
    void setPosition(const Entity& gameObject, const glm::vec3& position);
    [[nodiscard]] glm::vec3 getPosition(const Entity& gameObject) const;
    void setRotation(const Entity& gameObject, const glm::vec3& rotation);
    [[nodiscard]] glm::vec3 getRotation(const Entity& gameObject) const;
    void setScale(const Entity& gameObject, const glm::vec3& scale);
    [[nodiscard]] glm::vec3 getScale(const Entity& gameObject) const;

    [[nodiscard]] Entity getGameObjectWithTag(const std::string& tag) const;
    void setTag(const Entity& gameObject, const std::string& tag);
    [[nodiscard]] std::string getTag(const Entity& gameObject) const;
    void removeTag(const Entity& gameObject);
    [[nodiscard]] bool hasTag(const Entity& gameObject) const;

    void setMesh(const Entity& gameObject, Mesh& data);
    void setMesh(const Entity& gameObject, MeshHandle mesh);
    [[nodiscard]] MeshHandle getMesh(const Entity& gameObject) const;
    void removeMesh(const Entity& gameObject);
    [[nodiscard]] bool hasMesh(const Entity& gameObject) const;

    void setMaterial(const Entity& gameObject, Image& image);
    void setMaterial(const Entity& gameObject, TextureHandle textureHandle);
    TextureHandle getMaterial(const Entity& gameObject) const;
    void removeMaterial(const Entity& gameObject) const;
    bool hasMaterial(const Entity& gameObject) const;


    void setCamera(const Entity& gameObject, const Camera &camera);

    [[nodiscard]] const Camera *getCamera(const Entity &gameObject) const;
    void removeCamera(const Entity& gameObject);
    [[nodiscard]] bool hasCamera(const Entity& gameObject) const;

    void setPointer(const Entity& gameObject, void* pointer);
    [[nodiscard]] void* getPointer(const Entity& gameObject) const;
    void removePointer(const Entity& gameObject);
    [[nodiscard]] bool hasPointer(const Entity& gameObject) const;

    void setMainCamera(const Entity& gameObject);
    [[nodiscard]] Entity getMainCamera() const;
private:
    uint32_t sceneIndex = 0;
    EntityID cameraObject;

    rhi::RenderPacket createRenderPacket();

    std::vector<EntityID> entities;
};

}
