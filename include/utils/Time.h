//
// Created by Nemesis Verstraete on 26/07/2026.
//

#pragma once
#include <chrono>

namespace obsidium {

class Time {
public:
    float deltaTime();
private:
    bool firstFrame = true;
    std::chrono::steady_clock::time_point lastTime;
};

}
