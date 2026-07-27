//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once

namespace obsidium {

class Scene;
class World;

class Entity {
public:
    explicit Entity(World& world, EntityID id);

    bool operator==(const Entity& gameObject) const {
        return gameObject.id == id;
    }
private:
    World& world;
    EntityID id;
};

}
