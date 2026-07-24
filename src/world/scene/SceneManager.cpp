//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "../../include/scene/SceneManager.h"

namespace obsidium {

std::unique_ptr<SceneManager> SceneManager::create(MeshManager* meshManager) {
    auto sceneManager = std::make_unique<SceneManager>(SceneManager());
    sceneManager->meshManager = meshManager;
    sceneManager->createScene(true);
    return std::move(sceneManager);
}

void SceneManager::createScene(const bool load) {
    std::unique_ptr<Scene> s = Scene::create(meshManager, sceneIndex++);
    scenes.push_back(std::move(s));

    if (load || scene == nullptr) {
        scene = scenes.back().get();
    }
}

uint32_t SceneManager::activeSceneIndex() const {
    return sceneIndex;
}

void SceneManager::loadScene(uint32_t sceneIndex) {
    if (!isIndexInScenes(sceneIndex)) return;

    this->sceneIndex = sceneIndex;
    scene = scenes[sceneIndex].get();
}

bool SceneManager::isIndexInScenes(uint32_t sceneIndex) const {
    return (sceneIndex < scenes.size());
}

}
