//
// Created by Nemesis Verstraete on 17/07/2026.
//

#include <glm/glm.hpp>
#include <vulkan/vulkan_raii.hpp>

#include "../../../include/graphics/Mesh.h"

namespace obsidium::vulkan {

struct VulkanVertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 uv;

    static vk::VertexInputBindingDescription vertexBindingDescription() {
        return {
            .binding = 0,
            .stride = sizeof(VulkanVertex),
            .inputRate = vk::VertexInputRate::eVertex
        };
    }

    static std::array<vk::VertexInputAttributeDescription, 3> vertexAttributeDescriptions() {
        return {{
            {.location = 0, .binding = 0, .format = vk::Format::eR32G32B32Sfloat, .offset = offsetof(VulkanVertex, position)},
            {.location = 1, .binding = 0, .format = vk::Format::eR32G32B32Sfloat, .offset =  offsetof(VulkanVertex, color)},
            {.location = 2, .binding = 0, .format = vk::Format::eR32G32B32Sfloat, .offset = offsetof(VulkanVertex, uv)}
        }};
    }
};
}
