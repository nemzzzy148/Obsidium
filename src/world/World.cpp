//
// Created by Nemesis Verstraete on 22/07/2026.
//

#include "../../include/world/World.h"

namespace obsidium {

World::World(IDSystem<EntityID>* idSystem) {
    ECManager = std::make_unique<EntityComponentManager>(idSystem, 256);
    systemManager = std::make_unique<SystemManager>();
}

void World::updateSystems(const float dt) const {
    systemManager->updateAll(*ECManager, dt);
}

}
