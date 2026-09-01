//
// Created by Nemesis Verstraete on 06/08/2026.
//

#pragma once
#include <cstddef>

namespace obsidium {

enum class SamplerFilter {
    Point,
    Linear,
    Anisotropic
};

enum class SamplerWrap {
    Repeat,
    Clamp,
    Mirror,
    Border
};

struct SamplerState {
    SamplerFilter samplerFilter = SamplerFilter::Anisotropic;
    SamplerWrap samplerWrap = SamplerWrap::Repeat;
    bool operator==(const SamplerState& other) const {
        return other.samplerFilter == samplerFilter && other.samplerWrap == samplerWrap;
    }
};

}

template<>
struct std::hash<obsidium::SamplerState> {
    std::size_t operator() (const obsidium::SamplerState& state) const noexcept {
        const size_t h1 = std::hash<int>{}(static_cast<int>(state.samplerFilter));
        const size_t h2 = std::hash<int>{}(static_cast<int>(state.samplerWrap));

        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }

};