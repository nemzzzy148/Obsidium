//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once

#include <memory>
#include <vector>

#include "Scene.h"
#include "../../assets/MeshManager.h"

namespace obsidium {

class SceneManager {
public:
    void createScene(bool load = true);

    [[nodiscard]] uint32_t activeSceneIndex() const;
    void loadScene(uint32_t sceneIndex);

    [[nodiscard]] Scene& activeScene() const { return *scene; }
private:
    SceneManager() = default;
    static std::unique_ptr<SceneManager> create(MeshManager* meshManager);

    [[nodiscard]] bool isIndexInScenes(uint32_t sceneIndex) const;

    std::vector<std::unique_ptr<Scene>> scenes;
    uint sceneIndex = 0;
    Scene* scene = nullptr;

    MeshManager* meshManager = nullptr;
    friend class Engine;
};

}
