//
// Created by Nemesis Verstraete on 27/07/2026.
//

#pragma once

#include "../graphics/Renderer.h"

namespace obsidium {

class ShaderManager {
public:
    ShaderManager();
private:
    Renderer* renderer = nullptr;
};

}
