//
// Created by Nemesis Verstraete on 17/07/2026.
//

#include "Shader.h"

#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace obsidium {

Slang::ComPtr<slang::IGlobalSession> ShaderInstance::globalSession;
Slang::ComPtr<slang::ISession> ShaderInstance::session;

void ShaderInstance::initialize(ShaderFormat format) {
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

std::vector<char> ShaderInstance::generateCode(const std::string& filePath) {
    if (!session) {
        throw std::runtime_error("slang session was not initialized");
    }

    Slang::ComPtr<slang::IBlob> diagnostics;

    std::filesystem::path shaderPath = std::filesystem::absolute(filePath);
    if (!std::filesystem::exists(shaderPath)) {
        throw std::runtime_error("shader file not found: " + shaderPath.string());
    }

    std::string moduleName = shaderPath.replace_extension("").string();
    slang::IModule* module = session->loadModule(moduleName.c_str(), diagnostics.writeRef());
    if (diagnostics) {
        std::cerr << "[Slang] " << static_cast<const char *>(diagnostics->getBufferPointer()) << std::endl;
        diagnostics.setNull();
    }
    if (!module) {
        throw std::runtime_error("failed to load slang module: " + filePath);
    }

    Slang::ComPtr<slang::IEntryPoint> vertEntry, fragEntry;
    module->findEntryPointByName(vertexFunctionName.c_str(), vertEntry.writeRef());
    module->findEntryPointByName(fragmentFunctionName.c_str(), fragEntry.writeRef());
    if (!vertEntry) {
        throw std::runtime_error("could not find entry point '" + vertexFunctionName + "' in " + filePath);
    }
    if (!fragEntry) {
        throw std::runtime_error("could not find entry point '" + fragmentFunctionName + "' in " + filePath);
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
        std::cerr << "[Slang] " << static_cast<const char *>(diagnostics->getBufferPointer()) << std::endl;
        diagnostics.setNull();
    }
    if (SLANG_FAILED(result)) {
        throw std::runtime_error("failed to compose slang component type for: " + filePath);
    }

    Slang::ComPtr<slang::IComponentType> linkedProgram;
    result = program->link(linkedProgram.writeRef(), diagnostics.writeRef());
    if (diagnostics) {
        std::cerr << "[Slang] " << static_cast<const char *>(diagnostics->getBufferPointer()) << std::endl;
        diagnostics.setNull();
    }
    if (SLANG_FAILED(result)) {
        throw std::runtime_error("failed to link slang program for: " + filePath);
    }

    Slang::ComPtr<slang::IBlob> blob;
    result = linkedProgram->getTargetCode(0, blob.writeRef(), diagnostics.writeRef());
    if (diagnostics) {
        std::cerr << "[Slang] " << static_cast<const char *>(diagnostics->getBufferPointer()) << std::endl;
        diagnostics.setNull();
    }
    if (SLANG_FAILED(result) || !blob) {
        throw std::runtime_error("failed to generate code for: " + filePath);
    }

    const auto data = static_cast<const char *>(blob->getBufferPointer());
    const size_t size = blob->getBufferSize();
    return {data, data + size};
}

}