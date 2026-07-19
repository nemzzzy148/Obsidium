//
// Created by Nemesis Verstraete on 17/07/2026.
//

#pragma once

#include <vector>

#include <slang/slang.h>
#include <slang/slang-com-ptr.h>

namespace obsidium {

enum class ShaderFormat{ SPIRV };

class ShaderInstance {
public:
    ShaderInstance() = delete;

    static void initialize(ShaderFormat format = ShaderFormat::SPIRV);
    static std::vector<char> generateCode(const std::string& filePath);

    static constexpr std::string vertexFunctionName = "vertMain";
    static constexpr std::string fragmentFunctionName = "fragMain";
private:
    static Slang::ComPtr<slang::IGlobalSession> globalSession;
    static Slang::ComPtr<slang::ISession> session;
};

}
