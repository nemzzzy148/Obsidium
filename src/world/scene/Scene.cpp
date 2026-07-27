//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "../../../include/world/scene/Scene.h"

#include <ranges>

namespace obsidium {

Scene::Scene(SceneManager* manager, const uint32_t index) : index(index), manager(manager) {}

EntityID Scene::createEntity() const {
    return manager->ECManager.createEntity();
}

void Scene::destroyEntity(const EntityID id) const {
    manager->ECManager.destroyEntity(id);
}

template<Components C, typename Component>
ComponentType<C> & Scene::addComponent(EntityID id, Component component) {
    return manager->ECManager.addComponent<ComponentType<C>>(id, component);
}

template<Components C>
ComponentType<C> & Scene::getComponent(const EntityID id) {
    return manager->ECManager.getComponent<ComponentType<C>>(id);
}

template<Components C>
bool Scene::hasComponent(const EntityID id) const {
    return manager->ECManager.hasComponent<ComponentType<C>>(id);
}

template<Components C>
void Scene::enableComponent(const bool enable) const {
    manager->ECManager.enableComponent<ComponentType<C>>(enable);
}

template<Components C>
void Scene::removeComponent(const EntityID id) const {
    manager->ECManager.removeComponent<ComponentType<C>>(id);
}

}