//
// Created by Nemesis Verstraete on 23/07/2026.
//

#include "../../include/world/EntityComponentManager.h"

namespace obsidium {

EntityComponentManager::EntityComponentManager(const uint32_t entityCount) : idSystem(),
                                                                       dataSet(entityCount),
                                                                       tagSet(entityCount),
                                                                       transformSet(entityCount),
                                                                       meshSet(entityCount),
                                                                       materialSet(entityCount),
                                                                       cameraSet(entityCount),
                                                                       pointerSet(entityCount) {}

EntityID EntityComponentManager::createEntity() {
    const EntityID id = idSystem.allocate();
    transformSet.add(id, {});
    return id;
}

void EntityComponentManager::destroyEntity(const EntityID id) {
    idSystem.free(id);

    dataSet.remove(id);
    tagSet.remove(id);
    transformSet.remove(id);
    meshSet.remove(id);
    materialSet.remove(id);
    cameraSet.remove(id);
    pointerSet.remove(id);
}

void EntityComponentManager::hi() {
}

template<typename T>
T & EntityComponentManager::addComponent(EntityID id, T component) {
    return getSet<T>().add(id, component);
}

template<typename T>
T & EntityComponentManager::getComponent(EntityID id) {
    return getSet<T>().get(id);
}

template<typename T>
bool EntityComponentManager::hasComponent(EntityID id) {
    return getSet<T>().has(id);
}

template<typename T>
void EntityComponentManager::enableComponent(bool enable) {
    getSet<T>().
}

template<typename T>
void EntityComponentManager::removeComponent(EntityID id) {
    // cannot remove transform component
    if constexpr (std::is_same_v<T, TransformComponent>) return;
    getSet<T>().remove(id);
}

template<typename T>
SparseSet<T> & EntityComponentManager::getSet() {
    //if constexpr (std::is_same_v<T, EntityComponent>) return dataSet;
     if constexpr (std::is_same_v<T, TagComponent>) return tagSet;
    else if constexpr (std::is_same_v<T, TransformComponent>) return transformSet;
    else if constexpr (std::is_same_v<T, MeshComponent>) return meshSet;
    else if constexpr (std::is_same_v<T, MaterialComponent>) return materialSet;
    else if constexpr (std::is_same_v<T, CameraComponent>) return cameraSet;
    else if constexpr (std::is_same_v<T, PointerComponent>) return pointerSet;
    else throw std::runtime_error("type isn't compatible with ECS");
}
}
