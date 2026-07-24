//
// Created by Nemesis Verstraete on 23/07/2026.
//

#include "../../include/world/SparseSet.h"

namespace obsidium {

template<typename Component>
SparseSet<Component>::SparseSet(const uint32_t entityCount) {
    sparseSet = std::vector(entityCount, InvalidEntityIndex);
}

template<typename Component>
void SparseSet<Component>::add(const EntityID id, Component component) {
    if (id.index >= sparseSet.size()) sparseSet.resize(id.index + 1, InvalidEntityIndex);

    if (sparseSet[id.index] == InvalidEntityIndex) {
        entitySet.push_back(id);
        denseData.push_back(std::move(component));
        sparseSet[id.index] = entitySet.size() - 1;
    }
    else {
        if (entitySet[sparseSet[id.index]].version >= id.version) return;
        entitySet[sparseSet[id.index]] = id;
        denseData[sparseSet[id.index]] = std::move(component);
    }
}

template<typename Component>
void SparseSet<Component>::remove(const EntityID id) {
    if (!has(id)) return;
    entitySet[sparseSet[id.index]] = entitySet[entitySet.size() - 1];
    entitySet.pop_back();
    denseData[sparseSet[id.index]] = denseData[denseData.size() - 1];
    denseData.pop_back();
    sparseSet[id.index] = InvalidEntityIndex;
}

template<typename Component>
Component SparseSet<Component>::get(const EntityID id) {
    return denseData[sparseSet[id.index]];
}

template<typename Component>
bool SparseSet<Component>::has(const EntityID id) const {
    if (id.index >= sparseSet.size()) return false;
    if (sparseSet[id.index] == InvalidEntityIndex) return false;
    return entitySet[sparseSet[id.index]] == id;
}

}
