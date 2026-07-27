//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <memory>

#include "Components.h"
#include "Entity.h"
#include "../../assets/MeshManager.h"
#include "../EntityComponentManager.h"

namespace obsidium {

class SceneManager;

class Scene {
public:
    Scene(SceneManager* manager, uint32_t index);

    [[nodiscard]] EntityID createEntity() const;
    void destroyEntity(EntityID id) const;

    template<Components C, typename Component>
    ComponentType<C>& addComponent(EntityID id, Component component);

    template<Components C>
    ComponentType<C>& getComponent(EntityID id);

    template<Components C>
    [[nodiscard]] bool hasComponent(EntityID id) const;

    template<Components C>
    void enableComponent(bool enable = true) const;

    template<Components C>
    void removeComponent(EntityID id) const;
private:
    uint32_t index = 0;
    SceneManager* manager;
};

struct SceneEntry {
    std::string name;
    uint32_t index;
    std::vector<EntityID> ownedEntities;
    EntityID mainCamera = InvalidEntityID;
};

}
