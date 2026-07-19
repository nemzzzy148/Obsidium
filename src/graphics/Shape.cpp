//
// Created by Nemesis Verstraete on 17/07/2026.
//

#include "../../include/graphics/Shape.h"

namespace obsidium {

Mesh createMeshDataFromShape(Shape2D shape2d) {
    Mesh data;
    switch (shape2d) {
        case Shape2D::None:
            break;
        case Shape2D::Rectangle:
            data.vertices = {
                { {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
                { { 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f} },
                { { 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} },
                { {-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} }
            };
        case Shape2D::Circle:
            break;
        case Shape2D::Square:
            break;
        case Shape2D::Triangle:
            break;
        case Shape2D::Ellipse:
            break;
        case Shape2D::Polygon:
            break;
    }
    return std::move(data);
}

Mesh createMeshDataFromShape(Shape3D shape3d) {
}

}
