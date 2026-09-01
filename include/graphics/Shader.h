//
// Created by Nemesis Verstraete on 27/07/2026.
//

#pragma once
#include <glm/glm.hpp>

#include "../../src/rhi/Shader.h"
#include "../../src/utils/RefCounter.h"

namespace obsidium {
class Renderer;

namespace rhi {
class Shader;
}

enum class ShaderParameterType {
    None,
    Bool,
    Int32,
    UInt32,
    Float32,
    Vec2,
    Vec3,
    Vec4,
    Mat2x2,
    Mat3x3,
    Mat4x4,
    Texture2D,
    Sampler2D
};

template<ShaderParameterType T>
struct MapShaderType;

template<> struct MapShaderType<ShaderParameterType::Bool> { using type = bool; };
template<> struct MapShaderType<ShaderParameterType::Int32> { using type = int32_t; };
template<> struct MapShaderType<ShaderParameterType::UInt32> { using type = uint32_t; };
template<> struct MapShaderType<ShaderParameterType::Float32> { using type = float; }; // NEEDS TO BE 32 BIT
template<> struct MapShaderType<ShaderParameterType::Vec2> { using type = glm::vec2; };
template<> struct MapShaderType<ShaderParameterType::Vec3> { using type = glm::vec3; };
template<> struct MapShaderType<ShaderParameterType::Vec4> { using type = glm::vec4; };
template<> struct MapShaderType<ShaderParameterType::Mat2x2> { using type = glm::mat2x2; };
template<> struct MapShaderType<ShaderParameterType::Mat3x3> { using type = glm::mat3x3; };
template<> struct MapShaderType<ShaderParameterType::Mat4x4> { using type = glm::mat4x4; };
template<> struct MapShaderType<ShaderParameterType::Texture2D> { using type = uint32_t; };
template<> struct MapShaderType<ShaderParameterType::Sampler2D> { using type = uint32_t; };

template<ShaderParameterType T>
using ParameterType = MapShaderType<T>::type;

inline size_t shaderParameterSize(const ShaderParameterType type) {
    switch (type) {
        case ShaderParameterType::None: return 0;
        case ShaderParameterType::Bool: return sizeof(ParameterType<ShaderParameterType::Bool>);
        case ShaderParameterType::Int32: return sizeof(ParameterType<ShaderParameterType::Int32>);
        case ShaderParameterType::UInt32: return sizeof(ParameterType<ShaderParameterType::UInt32>);
        case ShaderParameterType::Float32: return sizeof(ParameterType<ShaderParameterType::Float32>);
        case ShaderParameterType::Vec2: return sizeof(ParameterType<ShaderParameterType::Vec2>);
        case ShaderParameterType::Vec3: return sizeof(ParameterType<ShaderParameterType::Vec3>);
        case ShaderParameterType::Vec4: return sizeof(ParameterType<ShaderParameterType::Vec4>);
        case ShaderParameterType::Mat2x2: return sizeof(ParameterType<ShaderParameterType::Mat2x2>);
        case ShaderParameterType::Mat3x3: return sizeof(ParameterType<ShaderParameterType::Mat3x3>);
        case ShaderParameterType::Mat4x4: return sizeof(ParameterType<ShaderParameterType::Mat4x4>);
        case ShaderParameterType::Texture2D: return sizeof(ParameterType<ShaderParameterType::Texture2D>);
        case ShaderParameterType::Sampler2D: return sizeof(ParameterType<ShaderParameterType::Sampler2D>);
    }
    return 0;
}

struct ShaderParameter {
    std::string name;
    ShaderParameterType type;
    uint8_t count = 0; // higher than 0 is an array
};

class Shader : public RefCounter {
public:
    static Shader create(const Renderer& renderer, std::vector<char> code);

    std::vector<ShaderParameter>& getParameters() { return parameters; }

    static size_t getSizeOfParameter(ShaderParameterType type);
private:
    Shader(std::unique_ptr<rhi::Shader> shader);
    rhi::Shader& getBackend() const { return *shader; }
    std::unique_ptr<rhi::Shader> shader;
    std::vector<ShaderParameter> parameters;

    friend class Renderer;
};

}