//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <memory>
#include <unordered_map>

#include "../../src/core/UUID.h"
#include "Components.h"
#include "GameObject.h"
#include "../graphics/MeshManager.h"

namespace obsidium {
class Shape;

class Scene {
public:
    GameObject createGameObject();
    void removeGameObject(const GameObject& gameObject);

    bool isGameObjectPresent(const GameObject& gameObject) const;

    void setTransform(const GameObject& gameObject, const TransformComponent &newTransform);
    [[nodiscard]] TransformComponent getTransform(const GameObject& gameObject) const;
    void setPosition(const GameObject& gameObject, const glm::vec3& position);
    [[nodiscard]] glm::vec3 getPosition(const GameObject& gameObject) const;
    void setRotation(const GameObject& gameObject, const glm::vec3& rotation);
    [[nodiscard]] glm::vec3 getRotation(const GameObject& gameObject) const;
    void setScale(const GameObject& gameObject, const glm::vec3& scale);
    [[nodiscard]] glm::vec3 getScale(const GameObject& gameObject) const;

    [[nodiscard]] GameObject getGameObjectWithTag(const std::string& tag) const;
    void setTag(const GameObject& gameObject, const std::string& tag);
    [[nodiscard]] std::string getTag(const GameObject& gameObject) const;
    void removeTag(const GameObject& gameObject);
    [[nodiscard]] bool hasTag(const GameObject& gameObject) const;

    void setMesh(const GameObject& gameObject, Mesh& data);
    void setMesh(const GameObject& gameObject, Shape& shape);
    void setMesh(const GameObject& gameObject, MeshHandle mesh);
    [[nodiscard]] MeshHandle getMesh(const GameObject& gameObject) const;
    void removeMesh(const GameObject& gameObject);
    [[nodiscard]] bool hasMesh(const GameObject& gameObject) const;

    void setCamera(const GameObject& gameObject, Camera camera);

    [[nodiscard]] const Camera *getCamera(const GameObject &gameObject) const;
    void removeCamera(const GameObject& gameObject);
    [[nodiscard]] bool hasCamera(const GameObject& gameObject) const;

    void setPointer(const GameObject& gameObject, void* pointer);
    [[nodiscard]] void* getPointer(const GameObject& gameObject) const;
    void removePointer(const GameObject& gameObject);
    [[nodiscard]] bool hasPointer(const GameObject& gameObject) const;

    void setMainCamera(const GameObject& gameObject);
    [[nodiscard]] GameObject getMainCamera() const;
private:
    static std::unique_ptr<Scene> create(MeshManager* meshManager, uint32_t sceneIndex);
    Scene() = default;

    uint32_t sceneIndex = 0;
    GameObject cameraObject;

    rhi::RenderPacket createRenderPacket();

    std::unordered_map<UUID_t, GameObject> gameObjects;
    std::unordered_map<UUID_t, TagComponent> tagComponents;
    std::unordered_map<UUID_t, TransformComponent> transformComponents;
    std::unordered_map<UUID_t, MeshComponent> meshComponents;
    std::unordered_map<UUID_t, CameraComponent> cameraComponents;
    std::unordered_map<UUID_t, PointerComponent> pointerComponents;

    MeshManager* meshManager = nullptr;

    friend class SceneManager;
    friend class Engine;
    friend class Renderer;
    friend class Scene;
};

}
