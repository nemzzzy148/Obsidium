//
// Created by Nemesis Verstraete on 17/07/2026.
//

#include "../../include/window/Window.h"

#include "GLFWImplementation.h"

namespace obsidium {

Window Window::create(int width, int height, const std::string& title) {
    Window window;
    window.backend = std::make_unique<GLFWImplementation>(width, height, title);
    return std::move(window);
}

}
