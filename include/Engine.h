//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <memory>

#include "../src/utils/IDSystem.h"
#include "graphics/Renderer.h"
#include "window/Window.h"
#include "world/World.h"
#include "world/scene/SceneManager.h"

namespace obsidium {

class Engine {
public:
    Engine();
    ~Engine();
    [[nodiscard]] SceneManager& sceneManager() const { return world->sceneManager(); }
    [[nodiscard]] Scene& activeScene() const { return world->activeScene(); }
    [[nodiscard]] Window& window() const { return *m_Window; }
    [[nodiscard]] Renderer& renderer() const { return *m_Render; }

    void update() const;
private:
    float lastTime = 0;

    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Renderer> m_Render;
    std::unique_ptr<AssetManager> assetManager;
    std::unique_ptr<World> world;
};

}
