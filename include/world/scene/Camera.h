//
// Created by Nemesis Verstraete on 16/07/2026.
//
#pragma once
#include <glm/glm.hpp>

namespace obsidium {

class Camera {
public:
    enum class Projection{ Perspective, Orthographic, Cavalier };

    explicit Camera(Projection projection = Projection::Perspective);

    [[nodiscard]] glm::mat4 getProjectionMat(float aspectRatio) const;

    static glm::mat4 getViewMat(glm::vec3 position, glm::vec3 rotation);

    // projection
    float perspectiveFOV = glm::radians(45.0f);
    float perspectiveNear = 0.01f;
    float perspectiveFar = 1000.0f;

    // orthographic
    float orthographicSize = 1.0f;
    float orthographicNear = -1000.0f;
    float orthographicFar = 1000.0f;

    // cavalier
    float cavalierSheerX = -0.5f;
    float cavalierSheerY = 0.5f;
    float angle = 45.0f;

private:
    Projection projection = Projection::Perspective;

    float aspectRatio = 1.0f;
};

struct CameraTransform {
    glm::mat4 view;
    Camera& camera;
};

}
