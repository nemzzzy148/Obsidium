//
// Created by Nemesis Verstraete on 19/07/2026.
//

#include "graphics/Texture.h"

#include <iostream>

#include "graphics/Renderer.h"
#include "stb_image/stb_image.h"

namespace obsidium {

Image::Image(const std::string &filePath, int width, int height) : width(width), height(height) {
    data = stbi_load(filePath.c_str(), &width, &height, nullptr, 4);

    if (data == nullptr) {
        std::cout << "failed to load image at path:" << filePath << std::endl;
    }
}

Image::~Image() {
    stbi_image_free(data);
}

Texture Texture::create(const Renderer &renderer, const uint32_t width, const uint32_t height,
    const TextureUsage usage, const TextureFormat format) {
    return renderer.createTexture(width, height, usage);
}

Texture::Texture(std::unique_ptr<rhi::Texture> texture) : backend(std::move(texture)) {}

}
