//
// Created by Nemesis Verstraete on 27/07/2026.
//

#pragma once
#include <memory>

#include "SamplerState.h"
#include "../../src/utils/RefCounter.h"

namespace obsidium {
namespace rhi {
class Sampler;
}

class Renderer;

class Sampler : public RefCounter {
public:
    static Sampler create(Renderer& renderer, SamplerState state);

    SamplerState getSamplerState() const;
private:
    explicit Sampler(std::unique_ptr<rhi::Sampler> backend);
    rhi::Sampler& getBackend() const { return *backend; }
    std::unique_ptr<rhi::Sampler> backend;
    friend class Renderer;
};

}
