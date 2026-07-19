//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <memory>

#include "graphics/Renderer.h"
#include "core/Window.h"
#include "scene/SceneManager.h"

namespace obsidium {

class Engine {
public:
    Engine();
    ~Engine();
    [[nodiscard]] SceneManager& sceneManager() const { return *m_SceneManager; }
    [[nodiscard]] Scene& activeScene() const { return m_SceneManager->activeScene(); }
    [[nodiscard]] Window& window() const { return *m_Window; }
    [[nodiscard]] Renderer& renderer() const { return *m_Render; }

    void update() const;
private:
    std::unique_ptr<Window> m_Window;
    std::unique_ptr<Renderer> m_Render;
    std::unique_ptr<SceneManager> m_SceneManager;
    std::unique_ptr<MeshManager> assetManager;

    friend class Scene;
};

}
