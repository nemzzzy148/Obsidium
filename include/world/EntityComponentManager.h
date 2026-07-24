//
// Created by Nemesis Verstraete on 23/07/2026.
//

#pragma once
#include <cstdint>

#include "SparseSet.h"
#include "scene/Components.h"

namespace obsidium {

class EntityComponentManager {
public:
    explicit EntityComponentManager(uint32_t entityCount);

    [[nodiscard]] EntityID createEntity();
    void destroyEntity(EntityID id);

    template<typename T>
    T &addComponent(EntityID id, T component);

    template<typename T>
    T& getComponent(EntityID id);

    template<typename T>
    bool hasComponent(EntityID id);

    template<typename T>
    void removeComponent(EntityID id);
private:
    template<typename T>
    SparseSet<T>& getSet();

    IDSystem<EntityID> idSystem;

    SparseSet<TagComponent> tagSet;
    SparseSet<TransformComponent> transformSet;
    SparseSet<MeshComponent> meshSet;
    SparseSet<MaterialComponent> materialSet;
    SparseSet<CameraComponent> cameraSet;
    SparseSet<PointerComponent> pointerSet;
};

}
