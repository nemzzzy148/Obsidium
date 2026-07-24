//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once

#include "world/World.h"

namespace obsidium {

class Scene;

class Entity {
public:
    explicit Entity(World& world);

    bool operator==(const Entity& gameObject) const {
        return gameObject.id == id;
    }
private:
    World& world;
    EntityID id;
};

}
