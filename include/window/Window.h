//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <memory>
#include <vector>

#include "../../src/window/WindowBackend.h"


namespace obsidium {
enum class WindowBackendType;

namespace rhi {
class Instance;
class Surface;
}

class Window {
public:
    static Window create(int width = 800, int height = 600, const std::string& title = "Game");
    
    [[nodiscard]] std::string getTitle() const {
        return backend->getTitle();
    }
    void setTitle(const std::string& title) const {
        backend->setTitle(title);
    }
    [[nodiscard]] uint32_t getWidth() const {
        return backend->getWidth();
    }
    void setWidth(const int width) const {
        backend->setWidth(width);
    }
    [[nodiscard]] uint32_t getHeight() const {
        return backend->getHeight();
    }
    void setHeight(const int height) const {
        backend->setHeight(height);
    }
    void getSize(int* width, int* height) const {
        backend->getSize(width, height);
    }
    void setSize(const int width, const int height) const {
        backend->setSize(width, height);
    }
    void setSize(const glm::ivec2 size) const {
        backend->setSize(size);
    }

    void getPosition(int* x, int* y) const {
        backend->getPosition(x, y);
    }
    void setPosition(const int x, const int y) const {
        backend->setPosition(x, y);
    }
    void setPosition(const glm::ivec2 position) const {
        backend->setPosition(position);
    }

    void getFrameBufferSize(int* width, int* height) const {
        backend->getFrameBufferSize(width, height);
    }

    [[nodiscard]] bool shouldClose() const {
        return backend->shouldClose();
    }
    void waitEvents() const {
        backend->waitEvents();
    }
private:
    WindowBackendType backendType = WindowBackendType::GLFW;

    std::unique_ptr<WindowBackend> backend;

    friend class Engine;
};

}
