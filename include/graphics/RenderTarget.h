//
// Created by Nemesis Verstraete on 06/08/2026.
//

#pragma once
#include <memory>

namespace obsidium {
namespace rhi {
class RenderTarget;
}

class RenderTarget {
public:

private:
    std::unique_ptr<rhi::RenderTarget> backend;
};

}
