//
// Created by Nemesis Verstraete on 19/07/2026.
//

#include "../../include/graphics/Model.h"

namespace obsidium {

Model::Model(ModelType type, const glm::vec3& color) {
    this->type = type;
}

Model::Model(const Mesh& mesh) {
    this->mesh = mesh;
}

}
