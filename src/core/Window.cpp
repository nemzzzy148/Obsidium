//
// Created by Nemesis Verstraete on 17/07/2026.
//

#include "../../include/core/Window.h"

#include "GLFWImplementation.h"

namespace obsidium {

std::unique_ptr<Window> Window::create(WindowBackend windowBackend, int width, int height, std::string title) {
    switch (windowBackend) {
        case WindowBackend::GLFW:
            return std::make_unique<GLFWImplementation>(GLFWImplementation(width, height, title));
    }
    return std::make_unique<GLFWImplementation>(GLFWImplementation(width, height, title));
}

WindowBackend Window::getBackend() {
    return backend;
}
}
