//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "../../../include/world/scene/SceneManager.h"

namespace obsidium {

SceneManager::SceneManager(EntityComponentManager &ECManager, const std::string &sceneName) : ECManager(ECManager) {
    createScene(sceneName);
}

uint32_t SceneManager::createScene(const std::string &sceneName, const bool load) {
    const auto entity = ECManager.createEntity();

    const uint32_t sceneIndex = scenes.size();
    SceneEntry entry{
        .name = sceneName,
        .index = sceneIndex
    };
    entry.ownedEntities.push_back(entity);
    scenes.push_back(std::move(entry));
    if (load) currentSceneIndex = sceneIndex;

    ECManager.addComponent<EntityComponent>(entity, {.name = "camera", .sceneIndex = sceneIndex});
    return sceneIndex;
}

Scene SceneManager::activeScene() {
    return {this, currentSceneIndex};
}

uint32_t SceneManager::activeSceneIndex() const {
    return currentSceneIndex;
}

const std::string & SceneManager::activeSceneName() const {
    return scenes[currentSceneIndex].name;
}


void SceneManager::loadScene(const uint32_t sceneIndex) {
    if (sceneIndex >= scenes.size()) return;
    for (const EntityID& id : scenes[currentSceneIndex].ownedEntities) {
        ECManager.destroyEntity(id);
    }
    scenes[currentSceneIndex].ownedEntities.clear();
    scenes[currentSceneIndex].mainCamera = InvalidEntityID;
    currentSceneIndex = sceneIndex;
    createSceneRequirements(currentSceneIndex);
}

void SceneManager::loadScene(const std::string &sceneName) {
    for (uint32_t i = 0; i < scenes.size(); i++) {
        if (scenes[i].name == sceneName) loadScene(i);
    }
}

void SceneManager::createSceneRequirements(const uint32_t sceneIndex) {
    if (!scenes[sceneIndex].ownedEntities.empty() && scenes[sceneIndex].mainCamera != InvalidEntityID)  return;
    const EntityID camera = createMainCamera(sceneIndex);
    scenes[sceneIndex].mainCamera = camera;
    scenes[sceneIndex].ownedEntities.push_back(camera);
}

EntityID SceneManager::createMainCamera(const uint32_t sceneIndex) const {
    const EntityID id = ECManager.createEntity();
    ECManager.addComponent<EntityComponent>(id, {.name = "camera", .sceneIndex = sceneIndex});
    ECManager.addComponent<CameraComponent>(id, {.camera = Camera()});
    return id;
}

}