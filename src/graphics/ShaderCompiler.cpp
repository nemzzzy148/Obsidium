//
// Created by Nemesis Verstraete on 06/08/2026.
//

#include "../../include/graphics/ShaderCompiler.h"

#include <filesystem>

#include "BackendShaderCompiler.h"
#include "../utils/Logger.h"

namespace obsidium {

void ShaderCompiler::initialize(const ShaderFormat format) {
    BackendShaderCompiler::initialize(format);
}

Slang::ComPtr<slang::IGlobalSession> ShaderCompiler::globalSession;
Slang::ComPtr<slang::ISession> ShaderCompiler::session;

Shader ShaderCompiler::createShader(Renderer& renderer, const std::string &filePath) {
    return std::move(BackendShaderCompiler::createShader(renderer, filePath));
}

}
