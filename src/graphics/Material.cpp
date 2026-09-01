//
// Created by Nemesis Verstraete on 27/07/2026.
//

#include "../../include/graphics/Material.h"

namespace obsidium {

Material::Material(Renderer& renderer, Shader &shader) : renderer(renderer), shader(std::move(shader)) {
    auto &shaderParameters = shader.getParameters();
    parameters.reserve(shaderParameters.size());

    size_t totalParameterSize = 0;
    for (size_t i = 0; i < shaderParameters.size(); i++) {
        parameters.try_emplace(shaderParameters[i].name, std::pair{shaderParameters[i], totalParameterSize});
        totalParameterSize += sizeof(shaderParameterSize(shaderParameters[i].type));
    }



}

template<typename V>
void Material::setParameter(std::string_view parameterName, ShaderParameterType) {
    if (std::is_same_v<V, >)
}

}