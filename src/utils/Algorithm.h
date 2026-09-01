//
// Created by Nemesis Verstraete on 01/08/2026.
//

#pragma once

namespace obsidium {

/**
 * Aligns up, only alignment with power of 2.
 */
template<typename T>
T alignUp(T alignment, T bytes) {
    return bytes + (alignment - 1) & ~(alignment - 1);
}

inline void coalesceAndFreeBufferRegions(std::vector<BufferRegion>& freeRegions, BufferRegion region) {
    bool merged = true;
    while (merged) {
        merged = false;
        for (size_t i = 0; i < freeRegions.size(); i++) {
            const auto [size, offset] = freeRegions[i];
            const bool leftAdjacent  = size + offset == region.offset;
            const bool rightAdjacent = region.size + region.offset == offset;
            if (leftAdjacent || rightAdjacent) {
                if (leftAdjacent) region.offset = offset;
                region.size += size;

                freeRegions.erase(freeRegions.begin() + i);
                merged = true;
                break;
            }
        }
    }
    freeRegions.push_back(region);
}

}