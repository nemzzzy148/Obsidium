//
// Created by Nemesis Verstraete on 19/07/2026.
//

#pragma once
#include "Mesh.h"
#include "../../src/rhi/Texture.h"
#include "../../src/utils/RefCounter.h"

namespace obsidium {
namespace rhi {
class Texture;
}

class Renderer;

enum class TextureFormat {
    RGBA8
};

constexpr size_t DefaultChannels = 4;

class Image : RefCounter {
public:
    Image(const std::string& filePath, int width, int height);

    [[nodiscard]] int getWidth() const { return width; }
    [[nodiscard]] int getHeight() const { return height; }
    [[nodiscard]] unsigned char* getData() const { return data; }
    [[nodiscard]] static TextureFormat getFormat() { return TextureFormat::RGBA8; }

    ~Image() override;
private:
    int width;
    int height;
    unsigned char* data = nullptr;

    friend class Renderer;
};

enum class TextureUsage : uint32_t {
    RenderTarget = 1 << 0,
    DepthStencil = 1 << 1,
    ShaderResource = 1 << 2,
    Storage = 1 << 3
};


class Texture : public RefCounter {
public:
    static Texture create(const Renderer& renderer, uint32_t width, uint32_t height,
        TextureUsage usage = TextureUsage::ShaderResource, TextureFormat format = TextureFormat::RGBA8);

    [[nodiscard]] size_t getSize() const { return backend->getSize(); }
    [[nodiscard]] uint32_t getWidth() const { return backend->getWidth(); }
    [[nodiscard]] uint32_t getHeight() const { return backend->getHeight(); }

    void* getNativeHandle() const { return backend.get(); }

    ~Texture() override {}
private:
    explicit Texture(std::unique_ptr<rhi::Texture> texture);
    rhi::Texture& getBackend() const { return *backend; }
    std::unique_ptr<rhi::Texture> backend;
    friend class Renderer;
};

}
