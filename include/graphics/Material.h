//
// Created by Nemesis Verstraete on 27/07/2026.
//

#pragma once

#include "Shader.h"

namespace obsidium {
class Texture;
class Sampler;

enum class MaterialType {
    Unlit,
    SimpleLit
};

//template<typename T>
//concept ShaderParameterTypeRequirement = std::is_same_v<T, int32_t>

class Material : public RefCounter {
public:
    explicit Material(Renderer& renderer, Shader& shader);

    void setParameter(std::string_view parameterName, ParameterType<ShaderParameterType::Bool> boolean);
    void setParameter(std::string_view parameterName, ParameterType<ShaderParameterType::Int> integer);
    void setParameter(std::string_view parameterName, ParameterType<ShaderParameterType::UInt> unsignedInteger);
    void setParameter(std::string_view parameterName, ParameterType<ShaderParameterType::Float> floatingPoint);
    void setParameter(std::string_view parameterName, ParameterType<ShaderParameterType::Vec2> vec2);
    void setParameter(std::string_view parameterName, ParameterType<ShaderParameterType::Vec3> vec3);
    void setParameter(std::string_view parameterName, ParameterType<ShaderParameterType::Vec4> vec4);
    void setParameter(std::string_view parameterName, ParameterType<ShaderParameterType::Mat2x2> mat2x2);
    void setParameter(std::string_view parameterName, ParameterType<ShaderParameterType::Mat3x3> mat3x3);
    void setParameter(std::string_view parameterName, ParameterType<ShaderParameterType::Mat4x4> mat4x4);
    void setParameter(std::string_view parameterName, const Sampler& sampler);
    void setParameter(std::string_view parameterName, const Texture& texture);
private:
    template<typename T>
    void setParameter(std::string_view parameterName, T value);

    void setupShaderParameterStorage(std::vector<ShaderParameter>& shaderParameters);
    std::vector<uint8_t> parameterStorage;
    std::unordered_map<std::string, std::pair<ShaderParameter, uint32_t>> parameters;

    Renderer& renderer;

    Shader shader;
};

}
