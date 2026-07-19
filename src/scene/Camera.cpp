//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "../../include/scene/Camera.h"

#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>

namespace obsidium {
Camera::Camera(Projection projection) {
    this->projection = projection;
}

glm::mat4 Camera::getProjectionMat() const {
    const float safeAspectRatio = aspectRatio > 0.0f ? aspectRatio : 1.0f;
    glm::mat4 p(1.0f);
    switch (projection) {
        case Projection::Perspective:
            p = glm::perspective(perspectiveFOV, safeAspectRatio, perspectiveNear, perspectiveFar);
            break;
        case Projection::Orthographic:
            p = glm::ortho(-orthographicSize * safeAspectRatio, orthographicSize * safeAspectRatio, -orthographicSize, orthographicSize, orthographicNear, orthographicFar);
            break;
    }
    return p;
}

inline float wrapDegrees(float degrees) {
    float wrapped = std::fmod(degrees, 360.0f);
    if (wrapped < 0.0f) {
        wrapped += 360.0f;
    }
    return wrapped;
}

inline glm::quat eulerToQuat(const glm::vec3& rotation) {
    const glm::vec3 wrapped = { wrapDegrees(rotation.x), wrapDegrees(rotation.y), wrapDegrees(rotation.z) };
    const glm::vec3 radians = glm::radians(wrapped);

    const glm::quat pitch = glm::angleAxis(radians.x, glm::vec3( 1.0f, 0.0f, 0.0f ));
    const glm::quat yaw = glm::angleAxis(radians.y, glm::vec3( 0.0f, 1.0f, 0.0f ));
    const glm::quat roll = glm::angleAxis(radians.z, glm::vec3( 0.0f, 0.0f, 1.0f ));

    return yaw * pitch * roll;
}

glm::mat4 Camera::getViewMat(const glm::vec3 position, const glm::vec3 rotation) {
    const glm::quat orientation = eulerToQuat(rotation);

    const glm::vec3 forward = glm::normalize(orientation * glm::vec3( 0.0f, 0.0f, -1.0f ));
    const glm::vec3 up = glm::normalize(orientation * glm::vec3( 0.0f, 1.0f, 0.0f ));

    return glm::lookAt(position, position + forward, up);
}

}
