//
// Created by Nemesis Verstraete on 19/07/2026.
//

#include <utility>

#include "../../include/graphics/Polygon.h"

namespace obsidium {

Polygon::Polygon(const PolygonType type) {
    this->type = type;
}

Polygon::Polygon(Mesh mesh) : mesh(std::move(mesh)) {

}

Mesh circleMesh() {
    Mesh mesh;
    return std::move(mesh);
}

Mesh squareMesh() {
    Mesh mesh;
    return std::move(mesh);
}


Mesh triangleMesh() {
    Mesh mesh;
    return std::move(mesh);
}


Mesh meshFromPolygon(const PolygonType type) {
    Mesh mesh;
    switch (type) {
        case PolygonType::Circle:
            mesh = circleMesh();
            break;
        case PolygonType::Square:
            break;
        case PolygonType::Triangle:
            break;
        case PolygonType::Polygon:
            break;
    }
    return std::move(mesh);
}

}
