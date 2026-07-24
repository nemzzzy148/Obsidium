//
// Created by Nemesis Verstraete on 22/07/2026.
//

#pragma once
#include <memory>

#include "EntityComponentManager.h"
#include "System.h"
#include "scene/SceneManager.h"

namespace obsidium {

class World {
public:
    explicit World(IDSystem<EntityID>* idSystem);

    void updateSystems(float dt) const;
private:
    std::unique_ptr<EntityComponentManager> ECManager;
    std::unique_ptr<SystemManager> systemManager;
    std::unique_ptr<SceneManager> sceneManager;
};

}
