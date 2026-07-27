//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "../../../include/world/scene/Scene.h"

#include "../../../include/world/scene/Entity.h"

namespace obsidium {

Entity::Entity(World& world, const EntityID id) : world(world), id(id) {}

}
