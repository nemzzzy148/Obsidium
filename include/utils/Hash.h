//
// Created by Nemesis Verstraete on 17/07/2026.
//

#pragma once
#include <cstdint>

namespace obsidium::hash {

inline uint64_t fnv1a(const void* data, size_t size) {
    const auto* bytes = static_cast<const uint8_t *>(data);
    uint64_t hash = 0xcbf29ce484222325ULL;
    for (size_t i = 0; i < size; i++) {
        hash ^= bytes[i];
        hash *= 0x100000001b3ULL;
    }
    return hash;
}

inline uint64_t fnv1aContinue(uint64_t hash, const void* data, size_t size) {
    const auto* bytes = static_cast<const uint8_t *>(data);
    for (size_t i = 0; i < size; i++) {
        hash ^= bytes[i];
        hash *= 0x100000001b3ULL;
    }
    return hash;
}

}
