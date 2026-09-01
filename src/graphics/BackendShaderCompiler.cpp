//
// Created by Nemesis Verstraete on 06/08/2026.
//

#include "BackendShaderCompiler.h"

#include <filesystem>
#include <iostream>

#include "../utils/Logger.h"
#include "graphics/Renderer.h"

namespace obsidium {

Slang::ComPtr<slang::IGlobalSession> BackendShaderCompiler::globalSession;
Slang::ComPtr<slang::ISession> BackendShaderCompiler::session;
bool BackendShaderCompiler::initialized = false;

void BackendShaderCompiler::initialize(const ShaderFormat format) {
    if (SLANG_FAILED(slang::createGlobalSession(globalSession.writeRef()))) {
        throw std::runtime_error("failed to create Slang global session");
    }

    slang::TargetDesc targetDesc;
    switch (format) {
        case ShaderFormat::SPIRV:
            targetDesc.format = SLANG_SPIRV;
            targetDesc.profile = globalSession->findProfile("spirv_1_4");
            targetDesc.flags = SLANG_TARGET_FLAG_GENERATE_SPIRV_DIRECTLY;
    }

    slang::CompilerOptionEntry vkEntryPointNameOption{
        .name = slang::CompilerOptionName::VulkanUseEntryPointName,
        .value = { .kind = slang::CompilerOptionValueKind::Int, .intValue0 = 1 }
    };

    slang::SessionDesc sessionDesc = {
        .targets = &targetDesc,
        .targetCount = 1,
        .defaultMatrixLayoutMode = SLANG_MATRIX_LAYOUT_COLUMN_MAJOR,
        .compilerOptionEntries = &vkEntryPointNameOption,
        .compilerOptionEntryCount = 1
    };

    const char* searchPaths[] = { "." };
    sessionDesc.searchPaths = searchPaths;
    sessionDesc.searchPathCount = 1;

    globalSession->createSession(sessionDesc, session.writeRef());
    if (!session) {
        throw std::runtime_error("failed to create slang session");
    }
}

Shader BackendShaderCompiler::createShader(Renderer &renderer, const std::string &filePath) {
    if (!initialized) {
        renderer.initializeShaderCompiler();
    }

    if (!session) {
        throw std::runtime_error("slang session was not initialized");
    }

    Slang::ComPtr<slang::IBlob> diagnostics;

    std::filesystem::path shaderPath = std::filesystem::absolute(filePath);
    if (!std::filesystem::exists(shaderPath)) {
        throw std::runtime_error("shader file not found: " + shaderPath.string());
    }

    const std::string moduleName = shaderPath.replace_extension("").string();
    slang::IModule* module = session->loadModule(moduleName.c_str(), diagnostics.writeRef());
    if (diagnostics) {
        std::cerr << "[Slang] " << static_cast<const char *>(diagnostics->getBufferPointer()) << std::endl;
        diagnostics.setNull();
    }
    if (!module) {
        throw std::runtime_error("failed to load slang module: " + filePath);
    }

    slang::ProgramLayout* moduleLayout = module->getLayout();
    Slang::ComPtr<slang::IEntryPoint> vertEntry, fragEntry;
    for (SlangInt32 i = 0; i < module->getDefinedEntryPointCount(); i++) {
        Slang::ComPtr<slang::IEntryPoint> entry;
        module->getDefinedEntryPoint(i, entry.writeRef());
        if (const SlangStage stage = moduleLayout->getEntryPointByIndex(i)->getStage();
                stage == SLANG_STAGE_VERTEX && !vertEntry) {
            vertEntry = entry;
        } else if (stage == SLANG_STAGE_FRAGMENT) {
            fragEntry = entry;
        }
    }
    if (!vertEntry) {
        LOG_ERROR("no \"[shader(\"vertex\")]\" shader entry point fount in", filePath);
    }
    if (!fragEntry) {
        LOG_ERROR("no \"[shader(\"fragment\")]\" shader entry point fount in", filePath);
    }

    const std::vector<slang::IComponentType*> components = {
        module, vertEntry.get(), fragEntry.get()
    };

    Slang::ComPtr<slang::IComponentType> program;
    SlangResult result = session->createCompositeComponentType(
        components.data(),
        static_cast<SlangInt>(components.size()),
        program.writeRef(),
        diagnostics.writeRef()
        );
    if (diagnostics) {
        LOG_WARNING("[Slang] ", static_cast<const char *>(diagnostics->getBufferPointer()));
        diagnostics.setNull();
    }
    if (SLANG_FAILED(result)) {
        throw std::runtime_error("failed to compose slang component type for: " + filePath);
    }

    Slang::ComPtr<slang::IComponentType> linkedProgram;
    result = program->link(linkedProgram.writeRef(), diagnostics.writeRef());
    if (diagnostics) {
        LOG_WARNING("[Slang] ", static_cast<const char *>(diagnostics->getBufferPointer()));
        diagnostics.setNull();
    }
    if (SLANG_FAILED(result)) {
        throw std::runtime_error("failed to link slang program for: " + filePath);
    }

    Slang::ComPtr<slang::IBlob> blob;
    result = linkedProgram->getTargetCode(0, blob.writeRef(), diagnostics.writeRef());
    if (diagnostics) {
        LOG_WARNING("[Slang] ", static_cast<const char *>(diagnostics->getBufferPointer()));
        diagnostics.setNull();
    }
    if (SLANG_FAILED(result) || !blob) {
        throw std::runtime_error("failed to generate code for: " + filePath);
    }

    const auto data = static_cast<const char *>(blob->getBufferPointer());
    const size_t size = blob->getBufferSize();

    slang::ProgramLayout* layout = linkedProgram->getLayout();
    auto shaderParameters = retrieveShaderParameters(layout);

    Shader shader;
    return {};
}

slang::VariableLayoutReflection* BackendShaderCompiler::findParameterByNameParameter(slang::ProgramLayout *layout, const std::string_view name) {
    for (uint32_t i = 0; i < layout->getParameterCount(); i++) {
        if (const auto parameter = layout->getParameterByIndex(i);
                strcmp(parameter->getName(), name.data()) == 0) {
            return parameter;
                }
    }
    return nullptr;
}

ShaderParameterType BackendShaderCompiler::getParameterType(slang::TypeLayoutReflection* typeLayout) {
    switch (typeLayout->getKind()) {
        case slang::TypeReflection::Kind::Matrix: {
            const unsigned rows = typeLayout->getRowCount();
            const unsigned columns = typeLayout->getColumnCount();
            if (const slang::TypeReflection::ScalarType scalar =
                    typeLayout->getType()->getElementType()->getScalarType();
                    scalar != slang::TypeReflection::Float32) {
                return ShaderParameterType::None;
            }
            if (rows == 2 && columns == 2) return ShaderParameterType::Mat2x2;
            if (rows == 3 && columns == 3) return ShaderParameterType::Mat3x3;
            if (rows == 4 && columns == 4) return ShaderParameterType::Mat4x4;
            return ShaderParameterType::None;

        }
        case slang::TypeReflection::Kind::Vector: {
            const unsigned n = typeLayout->getElementCount();
            if (const slang::TypeReflection::ScalarType scalar =
                    typeLayout->getType()->getElementType()->getScalarType();
                    scalar != slang::TypeReflection::Float32) {
                return ShaderParameterType::None;
            }
            switch (n) {
                case 2: return ShaderParameterType::Vec2;
                case 3: return ShaderParameterType::Vec3;
                case 4: return ShaderParameterType::Vec4;
                default: return ShaderParameterType::None;
            }

        }
        case slang::TypeReflection::Kind::Scalar: {
            switch (typeLayout->getScalarType()) {
                case slang::TypeReflection::Bool: return ShaderParameterType::Bool;
                case slang::TypeReflection::Int32: return ShaderParameterType::Int;
                case slang::TypeReflection::UInt32: return ShaderParameterType::UInt;
                case slang::TypeReflection::Float32: return ShaderParameterType::Float;
                default: return ShaderParameterType::None;
            }
        }
        case slang::TypeReflection::Kind::Struct: {
            if (strcmp(typeLayout->getType()->getName(), texture2DParamName.c_str()) == 0) {
                return ShaderParameterType::Texture2D;
            }
            if (strcmp(typeLayout->getType()->getName(), sampler2DParamName.c_str()) == 0) {
                return ShaderParameterType::Sampler2D;
            }
            return ShaderParameterType::None;
        }
        default: {
            return ShaderParameterType::None;
        }
    }
}

std::vector<ShaderParameter> BackendShaderCompiler::retrieveShaderParameters(slang::ProgramLayout* layout) {
    std::vector<ShaderParameter> result;
    for (uint32_t i = 0; i < layout->getParameterCount(); i++) {
        // search for parameter struct
        const auto param = layout->getParameterByIndex(i);
        auto type = param->getTypeLayout();
        while (type->getKind() == slang::TypeReflection::Kind::ConstantBuffer ||
               type->getKind() == slang::TypeReflection::Kind::ParameterBlock) {
            type = type->getElementTypeLayout();
        }

        // get parameters inside struct
        if (type->getKind() == slang::TypeReflection::Kind::Struct) {
            for (uint32_t j = 0; j < type->getFieldCount(); j++) {
                const auto field = type->getFieldByIndex(j);
                const auto fieldTypeLayout = field->getTypeLayout();
                if (fieldTypeLayout->getKind() == slang::TypeReflection::Kind::Array) {
                    const size_t count = fieldTypeLayout->getElementCount();
                    if (count > std::numeric_limits<uint8_t>::max()) {
                        LOG_ERROR("array field '", field->getName(), "' exceeds max length of ",
                               static_cast<int>(std::numeric_limits<uint8_t>::max()), " (has ", count, ")");
                        return {};
                    }
                    if (const auto elementType = getParameterType(fieldTypeLayout->getElementTypeLayout());
                            elementType != ShaderParameterType::None) {
                        result.push_back({field->getName(), elementType, static_cast<uint8_t>(count)});
                    } else {
                        LOG_WARNING("unsupported array element type '", fieldTypeLayout->getElementTypeLayout()->getType()->getName(),
                            "' for field '", field->getName(), "'");
                    }
                    continue;
                }
                if (const auto parameterType = getParameterType(fieldTypeLayout);
                        parameterType != ShaderParameterType::None) {
                    result.push_back({field->getName(), parameterType, 0});
                } else {
                    LOG_WARNING("unsupported field type '", fieldTypeLayout->getType()->getName(),
                        "' for field '", field->getName(), "'");
                }
            }
        }
    }
    if (result.empty()) {
        LOG_WARNING("slang shader takes no parameters. If you intended to take arguments, make sure you have an input struct named ", shaderParamStructName);
    }
    return result;
}

}
