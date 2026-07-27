//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "../include/Engine.h"

namespace obsidium {

Engine::Engine() {
    m_Window = Window::create();
    ShaderInstance::initialize();
    m_Render = Renderer::create(m_Window.get(), nullptr);
    assetManager = std::make_unique<AssetManager>(m_Render.get());
    world = std::make_unique<World>();
}

Engine::~Engine() {
    renderer().destroy();
}

void Engine::update() const {
    world->updateSystems();
}

}