//
// Created by Nemesis Verstraete on 22/07/2026.
//

#pragma once
#include <memory>

#include "EntityComponentManager.h"
#include "System.h"
#include "scene/SceneManager.h"
#include "utils/Time.h"

namespace obsidium {

class World {
public:
    World();

    void updateSystems(float dt) const;
    void updateSystems() const;

    [[nodiscard]] Scene activeScene() const;
    [[nodiscard]] SceneManager& sceneManager() const;

    [[nodiscard]] SystemManager& systemManager() const;

    [[nodiscard]] EntityComponentManager& ECManager() const;
private:
    std::unique_ptr<Time> m_Time;
    std::unique_ptr<EntityComponentManager> m_ECManager;
    std::unique_ptr<SystemManager> m_SystemManager;
    std::unique_ptr<SceneManager> m_SceneManager;

    friend class RenderSystem;
};

}
