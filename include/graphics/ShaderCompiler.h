//
// Created by Nemesis Verstraete on 06/08/2026.
//

#pragma once
#include <vector>

#include "Shader.h"
#include "slang/slang-com-ptr.h"

namespace obsidium {

enum class ShaderFormat{ SPIRV };

class ShaderCompiler {
public:
    ShaderCompiler() = delete;

    static void initialize(ShaderFormat format = ShaderFormat::SPIRV);
    static Shader createShader(Renderer& renderer, const std::string& filePath);

    static constexpr std::string shaderParamStructName = "Parameters";
private:

    static Slang::ComPtr<slang::IGlobalSession> globalSession;
    static Slang::ComPtr<slang::ISession> session;
};

}
