//
// Created by Nemesis Verstraete on 19/07/2026.
//

#include "Mesh.h"

namespace obsidium {

enum class ModelType {
    UVSphere,
    Icosphere,
    Cube,
    Cylinder,
    Cone,
    Pyramid,
    Torus,
    Capsule,
    Prism,
    Plane,
    Model
};

class Model {
public:
    Model(ModelType type = ModelType::Model, const glm::vec3& color = { 1.0f, 1.0f, 1.0f });
    Model(const Mesh& mesh);

    [[nodiscard]] ModelType getModelType() const { return type; }

    Mesh mesh;
private:
    ModelType type = ModelType::Model;
};

}

