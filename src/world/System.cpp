//
// Created by Nemesis Verstraete on 23/07/2026.
//

#include "../../include/world/System.h"

namespace obsidium {

void SystemManager::addSystem(std::unique_ptr<ISystem> system) {
    systems.push_back(std::move(system));
}

void SystemManager::updateAll(EntityComponentManager &ECManager, float dt) {
    for (const auto& system : systems) {
        system->update(ECManager, dt);
    }
}

}
