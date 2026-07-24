//
// Created by Nemesis Verstraete on 19/07/2026.
//

#pragma once
#include "Mesh.h"
#include "../../src/rhi/Texture.h"

namespace obsidium {

using TextureHandle = uint64_t;

constexpr TextureHandle InvalidTextureHandle = ~0;

constexpr size_t DefaultChannels = 4;

class Image {
public:
    Image(const std::string& filePath, int width, int height);
    ~Image();
private:
    int width;
    int height;
    unsigned char* data = nullptr;
    friend class Renderer;
};

class Texture {
public:
    [[nodiscard]] size_t getSize() const { return texture->getSize(); }
    [[nodiscard]] uint32_t getWidth() const { return texture->getWidth(); }
    [[nodiscard]] uint32_t getHeight() const { return texture->getHeight(); }
    [[nodiscard]] uint64_t getHash() const { return hash; }

private:
    void destroy();

    Texture() = default;
    std::unique_ptr<rhi::Texture> texture;

    uint64_t hash = ~0;
    friend class Renderer;
    friend class TextureManager;
};

}
