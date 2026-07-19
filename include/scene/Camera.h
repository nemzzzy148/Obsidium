//
// Created by Nemesis Verstraete on 16/07/2026.
//
#pragma once
#include <glm/glm.hpp>

namespace obsidium {

class Camera {
public:
    enum class Projection{ Perspective, Orthographic };

    explicit Camera(Projection projection = Projection::Perspective);

    glm::mat4 getProjectionMat() const;

    static glm::mat4 getViewMat(glm::vec3 position, glm::vec3 rotation);
private:
    Projection projection = Projection::Perspective;

    // projection
    float perspectiveFOV = glm::radians(45.0f);
    float perspectiveNear = 0.01f;
    float perspectiveFar = 1000.0f;

    // orthographic
    float orthographicSize = 1.0f;
    float orthographicNear = -1000.0f;
    float orthographicFar = 1000.0f;

    float aspectRatio = 1.0f;
};

}
