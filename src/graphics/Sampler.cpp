//
// Created by Nemesis Verstraete on 06/08/2026.
//

#include "../../include/graphics/Sampler.h"
#include "../rhi/Sampler.h"

#include "graphics/Renderer.h"

namespace obsidium {

Sampler Sampler::create(Renderer &renderer, const SamplerState state) {
    return renderer.createSampler(state);
}

Sampler::Sampler(std::unique_ptr<rhi::Sampler> backend) : backend(std::move(backend)) {}

SamplerState Sampler::getSamplerState() const { return backend->getSamplerState(); }

}