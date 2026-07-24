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
    assert(versions[id.index] == id.version && "ID is invalid");
    ++versions[id.index];
    freeSlots.push_back(id.version);
}

}
