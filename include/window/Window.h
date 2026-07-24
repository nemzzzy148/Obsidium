//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

namespace obsidium {

enum class WindowBackend {
    GLFW
};

class Window {
public:
    virtual ~Window() = default;

    virtual std::string getTitle() = 0;
    virtual void setTitle(const std::string& title) = 0;

    virtual int getWidth() = 0;
    virtual void setWidth(int width) = 0;
    virtual int getHeight() = 0;
    virtual void setHeight(int height) = 0;
    virtual void getSize(int* width, int* height) = 0;
    virtual glm::ivec2 getSize() = 0;
    virtual void setSize(int width, int height) = 0;
    virtual void setSize(glm::ivec2 size) = 0;

    virtual void getPosition(int* x, int* y) = 0;
    virtual glm::ivec2 getPosition() = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual void setPosition(glm::ivec2 position) = 0;

    virtual void getFrameBufferSize(int* width, int* height) = 0;

    virtual bool shouldClose() = 0;
    virtual void waitEvents() = 0;

    virtual std::vector<const char*> getRequiredInstanceExtensions() = 0;

    virtual void* getNativeWindowHandle() = 0;
    virtual WindowBackend getBackend() = 0;
private:
    WindowBackend backend = WindowBackend::GLFW;
    static std::unique_ptr<Window> create(WindowBackend windowBackend = WindowBackend::GLFW,
        int width = 800, int height = 600, std::string title = "Game");

    friend class Engine;
};

}
