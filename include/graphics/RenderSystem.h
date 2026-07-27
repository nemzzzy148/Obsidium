//
// Created by Nemesis Verstraete on 24/07/2026.
//

#pragma once
#include "../world/System.h"

namespace obsidium {

class World;
class Renderer;

class RenderSystem : public ISystem {
public:
    explicit RenderSystem(Renderer& renderer);
    void update(World &world, float dt) override;
private:
    Renderer& renderer;
};

}
