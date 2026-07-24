//
// Created by Nemesis Verstraete on 17/07/2026.
//

#pragma once
#include <glfw/glfw3.h>

#include "../../include/window/Window.h"

namespace obsidium {
class GLFWImplementation : public Window {
public:
    std::string getTitle() override {
        return glfwGetWindowTitle(window);
    }
    void setTitle(const std::string &title) override {
        glfwSetWindowTitle(window, title.c_str());
    }

    int getWidth() override {
        int width;
        glfwGetWindowSize(window, &width, nullptr);
        return width;
    }
    void setWidth(int width) override {
        glfwSetWindowSize(window, width, getHeight());
    }

    int getHeight() override {
        int height;
        glfwGetWindowSize(window, nullptr, &height);
        return height;
    }
    void setHeight(const int height) override {
        glfwSetWindowSize(window, getWidth(), height);
    }

    void getSize(int *width, int *height) override {
        glfwGetWindowSize(window, width, height);
    }
    glm::ivec2 getSize() override {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        return {width, height};
    }


    void setSize(const int width, const int height) override {
        glfwSetWindowSize(window, width, height);
    }
    void setSize(glm::ivec2 size) override {
        glfwSetWindowSize(window, size.x, size.y);
    }

    void getPosition(int* x, int* y) override {
        glfwGetWindowPos(window, x, y);
    }
    glm::ivec2 getPosition() override {
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        return {x, y};
    }

    void setPosition(int x, int y) override {
        glfwSetWindowPos(window, x, y);
    }
    void setPosition(glm::ivec2 position) override {
        glfwSetWindowPos(window, position.x, position.y);
    }


    void getFrameBufferSize(int* width, int* height) override {
        glfwGetFramebufferSize(window, width, height);
    }

    bool shouldClose() override {
        glfwPollEvents();
        return glfwWindowShouldClose(window);
    }
    void waitEvents() override { glfwWaitEvents(); }

    std::vector<char const *> getRequiredInstanceExtensions() override {
        uint32_t extensionCount = 0;
        auto extensions = glfwGetRequiredInstanceExtensions(&extensionCount);

        return {extensions, extensions + extensionCount};
    }

    void* getNativeWindowHandle() override { return static_cast<void *>(window); }
    WindowBackend getBackend() override { return WindowBackend::GLFW; }
private:
    GLFWImplementation(int width, int height, std::string& title) {
        if (!glfwInit()) throw std::runtime_error("failed to initialize glfw");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, true);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("failed to create glfw window");
        }
    }

    GLFWwindow* window = nullptr;

    friend class Window;
};

}