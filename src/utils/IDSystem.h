//
// Created by Nemesis Verstraete on 23/07/2026.
//

#pragma once
#include <unordered_map>
#include <vector>

namespace obsidium {

struct AssetID {
    uint32_t index;
    uint32_t version;

    uint64_t hash = ~0;
    bool operator==(const AssetID& other) const {
        return index == other.index && version == other.version && hash == other.hash;
    }
};

using EntityIndex = uint32_t;
constexpr EntityIndex InvalidEntityIndex = ~0;

struct EntityID {
    EntityIndex index;
    EntityIndex version;
    bool operator==(const EntityID& other) const {
        return index == other.index && version == other.version;
    }
};

constexpr auto InvalidAssetID = AssetID{.index = 0, .version = 0};
constexpr auto InvalidEntityID = EntityID{.index = 0, .version = 0};

template<typename T>
concept ID = std::same_as<T ,AssetID> || std::same_as<T, EntityID>;

template<ID T>
class IDSystem {
public:
    IDSystem() = default;
    T allocate();
    void free(T id);

    bool valid(T id) const;
private:
    std::vector<uint32_t> freeSlots;
    std::vector<uint32_t> versions;

    uint32_t currentIndex = 0;
};

}

template<>
struct std::hash<obsidium::AssetID> {
    std::size_t operator() (const obsidium::AssetID& id) const noexcept {
        const size_t h1 = std::hash<uint32_t>{}(id.index);
        const size_t h2 = std::hash<uint32_t>{}(id.version);
        const size_t h3 = std::hash<uint64_t>{}(id.hash);

        size_t seed = h1 ^ h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
        seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);

        return seed;
    }
};

template<>
struct std::hash<obsidium::EntityID> {
    std::size_t operator() (const obsidium::EntityID& id) const noexcept {
        const size_t h1 = std::hash<obsidium::EntityIndex>{}(id.index);
        const size_t h2 = std::hash<obsidium::EntityIndex>{}(id.version);

        return h1 ^ h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
    }
};
