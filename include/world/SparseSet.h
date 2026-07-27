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
    void enable(EntityID id, bool enable);

    [[nodiscard]] const std::vector<EntityID>& getEntitySet() const { return entitySet; }
    [[nodiscard]] const std::vector<Component>& getDataSet() const { return entitySet; }
private:
    std::vector<EntityIndex> sparseSet;

    // dense set
    std::vector<EntityID> entitySet;
    std::vector<Component> denseData;
};

}
