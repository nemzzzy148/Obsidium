//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "../include/Engine.h"

namespace obsidium {

Engine::Engine() {
    m_Window = Window::create();
    ShaderInstance::initialize();
    m_Render = Renderer::create(m_Window.get(), nullptr);
    assetManager = MeshManager::create(*m_Render);
    m_Render->backend->assetManager = assetManager.get();
    m_SceneManager = SceneManager::create(assetManager.get());
}

Engine::~Engine() {
    renderer().destroy();
}

void Engine::update() const {
    renderer().renderScene(activeScene());
}

}