//
// Created by Nemesis Verstraete on 23/07/2026.
//

#include "IDSystem.h"

#include <cassert>

namespace obsidium {

template<ID T>
T IDSystem<T>::allocate() {
    T id;
    if (!freeSlots.empty()) {
        id.index = freeSlots.back();
        freeSlots.pop_back();
    }
    else {
        id.index = currentIndex++;
        versions.push_back(1);
    }
    id.version = versions[id.index];
    return id;
}

template<ID T>
void IDSystem<T>::free(T id) {
    assert(id.index < currentIndex && "index out of bounds");
    assert(versions[id.index] == id.version && "ID is invalid");

    ++versions[id.index];
    freeSlots.push_back(id.index);
}

template<ID T>
bool IDSystem<T>::valid(T id) const {
    if (id.index >= currentIndex) {
        return false;
    }
    return versions[id.index] == id.version;
}

}
