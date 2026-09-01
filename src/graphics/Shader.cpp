//
// Created by Nemesis Verstraete on 05/08/2026.
//

#include "../../include/graphics/Shader.h"

#include "graphics/Renderer.h"

namespace obsidium {

Shader Shader::create(const Renderer &renderer, std::vector<char> code) {
    return renderer.createShader(std::move(code));
}

size_t Shader::getSizeOfParameter(ShaderParameterType type) {
    switch ()
}

Shader::Shader(std::unique_ptr<rhi::Shader> shader) : shader(std::move(shader)) {}

}