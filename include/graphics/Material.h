//
// Created by Nemesis Verstraete on 27/07/2026.
//

#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

namespace obsidium {
struct AssetID;

class Material {
public:
private:

};

struct MaterialProperties { // push constants / texture
    std::unordered_map<std::string, AssetID> textures;
    std::unordered_map<std::string, float> floats;
    std::unordered_map<std::string, int> integers;
    std::unordered_map<std::string, glm::vec2> vector2s;
    std::unordered_map<std::string, glm::vec3> vector3s;
    std::unordered_map<std::string, glm::vec4> vector4s;
    // gradient implementation
    std::unordered_map<std::string, glm::mat2> matrix2s;
    std::unordered_map<std::string, glm::mat3> matrix3s;
    std::unordered_map<std::string, glm::mat4> matrix4s;
};

}
