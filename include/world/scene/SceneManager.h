//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once

#include <memory>
#include <vector>

#include "Scene.h"
#include "../../assets/MeshManager.h"
#include "../EntityComponentManager.h"

namespace obsidium {

class SceneManager {
public:
    explicit SceneManager(EntityComponentManager& ECManager, const std::string& sceneName = "scene");

    uint32_t createScene(const std::string& sceneName, bool load = true);

    Scene activeScene();
    const std::vector<EntityID>& activeSceneObjects();
    [[nodiscard]] uint32_t activeSceneIndex() const;
    [[nodiscard]] const std::string& activeSceneName() const;
    void loadScene(uint32_t sceneIndex);
    void loadScene(const std::string& sceneName);
private:
    void createSceneRequirements(uint32_t sceneIndex);
    [[nodiscard]] EntityID createMainCamera(uint32_t sceneIndex) const;

    std::vector<SceneEntry> scenes;
    uint32_t currentSceneIndex = 0;

    EntityComponentManager& ECManager;

    friend class Scene;
};

}
