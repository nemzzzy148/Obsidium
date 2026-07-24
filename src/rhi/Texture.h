//
// Created by Nemesis Verstraete on 16/07/2026.
//

#pragma once

namespace obsidium::rhi {

class Texture {
public:
    [[nodiscard]] size_t getSize() const { return size; }
    [[nodiscard]] uint32_t getWidth() const { return width; }
    [[nodiscard]] uint32_t getHeight() const { return height; }

    virtual void destroy() = 0;
private:
    size_t size = 0;
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t channels = 4; // rgba
};

}
