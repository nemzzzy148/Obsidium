//
// Created by Nemesis Verstraete on 17/07/2026.
//

#pragma once
#include <glfw/glfw3.h>

#include "WindowBackend.h"
#include "window/Window.h"
#include "../../include/window/Window.h"

namespace obsidium {

class GLFWImplementation : public WindowBackend {
public:
    GLFWImplementation(const int width, const int height, const std::string& title) {
        if (!glfwInit()) throw std::runtime_error("failed to initialize glfw");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, true);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("failed to create glfw window");
        }
    }

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


    void setSize(const int width, const int height) override {
        glfwSetWindowSize(window, width, height);
    }

    void getPosition(int* x, int* y) override {
        glfwGetWindowPos(window, x, y);
    }

    void setPosition(const int x, const int y) override {
        glfwSetWindowPos(window, x, y);
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

    void* getNativeWindowHandle() override { return window; }
    WindowBackendType getBackend() override { return WindowBackendType::GLFW; }
private:

    GLFWwindow* window = nullptr;

    friend class Window;
};

}
