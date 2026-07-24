//
// Created by Nemesis Verstraete on 23/07/2026.
//

#pragma once
#include <vector>

#include "../../src/utils/IDSystem.h"

namespace obsidium {

template<typename Component>
class SparseSet {
public:
    explicit SparseSet(uint32_t entityCount);
    void add(EntityID id, Component component);
    void remove(EntityID id);
    Component get(EntityID id);
    [[nodiscard]] bool has(EntityID id) const;
private:
    std::vector<EntityIndex> sparseSet;

    // dense set
    std::vector<EntityID> entitySet;
    std::vector<Component> denseData;
};

}
