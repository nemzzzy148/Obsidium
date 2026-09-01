//
// Created by Nemesis Verstraete on 17/07/2026.
//

#pragma once
#include <cstdint>

namespace obsidium::hash {

constexpr uint64_t fnv1aHash = 0xcbf29ce484222325ULL;

inline uint64_t fnv1a(const void* data, const size_t size) {
    const auto* bytes = static_cast<const uint8_t *>(data);
    uint64_t hash = fnv1aHash;
    for (size_t i = 0; i < size; i++) {
        hash ^= bytes[i];
        hash *= 0x100000001b3ULL;
    }
    return hash;
}

inline uint64_t fnv1aContinue(uint64_t hash, const void* data, const size_t size) {
    const auto* bytes = static_cast<const uint8_t *>(data);
    for (size_t i = 0; i < size; i++) {
        hash ^= bytes[i];
        hash *= 0x100000001b3ULL;
    }
    return hash;
}

template<typename... T>
uint64_t fnv1a(T... args) {
    uint64_t hash = fnv1aHash;
    ((hash = fnv1aContinue(hash, static_cast<const void *>(&args), sizeof(T))), ...);
    return hash;
}

}
