//
// Created by Nemesis Verstraete on 13/08/2026.
//

#pragma once
#include <string>
#include <vector>

namespace obsidium {

namespace rhi {
class Instance;
class Surface;
}

enum class WindowBackendType {
    GLFW
};

class WindowBackend {
public:
    virtual ~WindowBackend() = default;

    virtual std::string getTitle() = 0;
    virtual void setTitle(const std::string& title) = 0;

    virtual int getWidth() = 0;
    virtual void setWidth(int width) = 0;
    virtual int getHeight() = 0;
    virtual void setHeight(int height) = 0;
    virtual void getSize(int* width, int* height) = 0;
    virtual void setSize(int width, int height) = 0;

    virtual void getPosition(int* x, int* y) = 0;
    virtual void setPosition(int x, int y) = 0;

    virtual void getFrameBufferSize(int* width, int* height) = 0;

    virtual bool shouldClose() = 0;
    virtual void waitEvents() = 0;

    virtual std::vector<const char*> getRequiredInstanceExtensions() = 0;

    virtual void* getNativeWindowHandle() = 0;
    virtual WindowBackendType getBackend() = 0;
};

}
