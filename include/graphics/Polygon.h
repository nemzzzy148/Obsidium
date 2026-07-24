//
// Created by Nemesis Verstraete on 19/07/2026.
//

#pragma once
#include "Mesh.h"

namespace obsidium {

enum class PolygonType {
    Circle,
    Square,
    Triangle,
    Polygon
};

class Polygon {
    Polygon(PolygonType type);
    Polygon(Mesh  mesh);

    [[nodiscard]] PolygonType getPolygonType() const { return type; }

    Mesh mesh;
private:
    PolygonType type = PolygonType::Polygon;
};

}