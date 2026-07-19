cmake_minimum_required(VERSION 4.2)
project(Obsidium)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Vulkan REQUIRED)

find_package(glfw3 REQUIRED)

include_directories(/opt/homebrew/include)

add_library(Obsidium SHARED
        include/core/Window.h
        include/Engine.h
        include/graphics/Renderer.h
        src/Engine.cpp
        src/graphics/vulkan/VulkanContext.cpp
        src/graphics/vulkan/VulkanContext.h
        src/graphics/vulkan/VulkanDevice.cpp
        src/graphics/vulkan/VulkanDevice.h
        src/graphics/vulkan/VulkanSurface.h
        src/graphics/vulkan/VulkanSwapchain.cpp
        src/graphics/vulkan/VulkanSwapchain.h
        src/graphics/vulkan/VulkanRenderer.cpp
        src/graphics/vulkan/VulkanRenderer.h
        src/rhi/RendererBackend.h
        src/rhi/Buffer.h
        src/rhi/Texture.h
        src/rhi/RenderPacket.h
        src/graphics/Renderer.cpp
        src/graphics/vulkan/VulkanFrameContext.h
        src/graphics/vulkan/VulkanPipeline.cpp
        src/graphics/vulkan/VulkanPipeline.h
        src/scene/Scene.cpp
        include/scene/Scene.h
        include/scene/Components.h
        src/scene/GameObject.cpp
        include/scene/GameObject.h
        src/core/UUID.cpp
        src/core/UUID.h
        src/scene/Camera.cpp
        include/scene/Camera.h
        src/scene/SceneManager.cpp
        include/scene/SceneManager.h
        src/graphics/MeshManager.cpp
        include/graphics/MeshManager.h
        src/graphics/vulkan/VulkanBuffer.cpp
        src/graphics/vulkan/VulkanBuffer.h
        include/graphics/Mesh.h
        src/graphics/vulkan/VulkanCommandPool.cpp
        src/graphics/vulkan/VulkanCommandPool.h
        src/graphics/vulkan/VulkanCommandBuffers.cpp
        src/graphics/vulkan/VulkanCommandBuffers.h
        include/Application.h
        src/graphics/shader/Shader.cpp
        src/graphics/shader/Shader.h
        src/graphics/vulkan/Mesh.h
        include/graphics/Shape.h
        src/graphics/Shape.cpp
        include/core/Hash.h
        src/core/Window.cpp
        src/core/GLFWImplementation.h
        src/graphics/vulkan/VulkanDescriptors.cpp
        src/graphics/vulkan/VulkanDescriptors.h
        include/graphics/TextureManager.h
        src/rhi/RendererBackend.cpp
        include/Obsidium.h
        src/graphics/Polygon.cpp
        include/graphics/Polygon.h
)

target_include_directories(Obsidium PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

enable_testing()

add_subdirectory(sandbox)


target_compile_definitions(Obsidium PUBLIC VULKAN_HPP_NO_STRUCT_CONSTRUCTORS)

target_link_libraries(Obsidium
        Vulkan::Vulkan
        glfw
        slang
)