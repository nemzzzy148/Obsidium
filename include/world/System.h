//
// Created by Nemesis Verstraete on 23/07/2026.
//

#pragma once
#include "EntityComponentManager.h"

namespace obsidium {

class World;

class ISystem {
public:
    virtual ~ISystem() = default;
    virtual void update(World &world, float dt);
};

class SystemManager {
public:
    void addSystem(std::unique_ptr<ISystem> system);
    void updateAll(EntityComponentManager& ECManager, float dt);
private:
    std::vector<std::unique_ptr<ISystem>> systems;
};

}
