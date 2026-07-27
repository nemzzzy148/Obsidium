//
// Created by Nemesis Verstraete on 26/07/2026.
//

#include "../../include/utils/Time.h"

#include <chrono>

namespace obsidium {

float Time::deltaTime() {
    const auto currentTime = std::chrono::steady_clock::now();
    if (firstFrame) {
        lastTime = currentTime;
        firstFrame = false;
        return 0.0f;
    }
    const std::chrono::duration<float> deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    return deltaTime.count();
}

}
