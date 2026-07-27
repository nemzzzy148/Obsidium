//
// Created by Nemesis Verstraete on 22/07/2026.
//

#include "../../include/world/World.h"

namespace obsidium {

World::World() {
    m_Time = std::make_unique<Time>();
    m_ECManager = std::make_unique<EntityComponentManager>(256);
    m_SystemManager = std::make_unique<SystemManager>();
    m_SceneManager = std::make_unique<SceneManager>(ECManager());
}

void World::updateSystems(const float dt) const {
    m_SystemManager->updateAll(*m_ECManager, dt);
}

void World::updateSystems() const {
    updateSystems(m_Time->deltaTime());
}

Scene World::activeScene() const {
    return m_SceneManager->activeScene();
}

SceneManager & World::sceneManager() const {
    return *m_SceneManager;
}

SystemManager & World::systemManager() const {
    return *m_SystemManager;
}

EntityComponentManager & World::ECManager() const {
    return *m_ECManager;
}

}
