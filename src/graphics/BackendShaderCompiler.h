//
// Created by Nemesis Verstraete on 06/08/2026.
//

#pragma once
#include <slang/slang.h>
#include <slang/slang-com-ptr.h>
#include <vector>

#include "graphics/ShaderCompiler.h"

namespace slang {
struct IGlobalSession;
}

namespace obsidium {

class BackendShaderCompiler {
public:
    BackendShaderCompiler() = delete;
    static void initialize(ShaderFormat format = ShaderFormat::SPIRV);
    static Shader createShader(Renderer& renderer, const std::string& filePath);

    static constexpr std::string shaderParamStructName = "Parameters";
    static constexpr std::string texture2DParamName = "Texture2DHandle";
    static constexpr std::string sampler2DParamName = "Sampler2DHandle";
private:
    static slang::VariableLayoutReflection* findParameterByNameParameter(slang::ProgramLayout* layout, std::string_view name);
    static ShaderParameterType getParameterType(slang::TypeLayoutReflection* typeLayout);
    static std::vector<ShaderParameter> retrieveShaderParameters(slang::ProgramLayout* layout);

    static bool initialized;

    static Slang::ComPtr<slang::IGlobalSession> globalSession;
    static Slang::ComPtr<slang::ISession> session;
};

}
