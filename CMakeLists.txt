cmake_minimum_required(VERSION 4.2)
project(Obsidium)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Vulkan REQUIRED)

find_package(glfw3 REQUIRED)

include_directories(/opt/homebrew/include)

add_library(Obsidium SHARED
        include/window/Window.h
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
        src/world/scene/Scene.cpp
        include/world/scene/Scene.h
        include/world/scene/Components.h
        src/world/scene/Entity.cpp
        include/world/scene/Entity.h
        src/utils/UUID.cpp
        src/utils/UUID.h
        src/world/scene/Camera.cpp
        include/world/scene/Camera.h
        src/world/scene/SceneManager.cpp
        include/world/scene/SceneManager.h
        src/assets/MeshManager.cpp
        include/assets/MeshManager.h
        src/graphics/vulkan/VulkanBuffer.cpp
        src/graphics/vulkan/VulkanBuffer.h
        include/graphics/Mesh.h
        src/graphics/vulkan/VulkanCommandPool.cpp
        src/graphics/vulkan/VulkanCommandPool.h
        src/graphics/vulkan/VulkanCommandBuffers.cpp
        src/graphics/vulkan/VulkanCommandBuffers.h
        src/graphics/shader/Shader.cpp
        src/graphics/shader/Shader.h
        src/graphics/vulkan/Mesh.h
        include/utils/Hash.h
        src/window/Window.cpp
        src/window/GLFWImplementation.h
        src/graphics/vulkan/VulkanDescriptors.cpp
        src/graphics/vulkan/VulkanDescriptors.h
        include/assets/TextureManager.h
        src/rhi/RendererBackend.cpp
        include/Obsidium.h
        src/graphics/Polygon.cpp
        include/graphics/Polygon.h
        src/graphics/Model.cpp
        include/graphics/Model.h
        include/graphics/Texture.h
        src/graphics/Texture.cpp
        src/assets/TextureManager.cpp
        thirdparty/stb_image/stb_image.cpp
        src/graphics/vulkan/VulkanTexture.h
        src/graphics/vulkan/VulkanTexture.cpp
        include/graphics/Buffer.h
        src/graphics/Buffer.cpp
        src/world/World.cpp
        include/world/World.h
        src/utils/IDSystem.cpp
        src/utils/IDSystem.h
        src/world/SparseSet.cpp
        include/world/SparseSet.h
        src/world/EntityComponentManager.cpp
        include/world/EntityComponentManager.h
        src/world/System.cpp
        include/world/System.h
        src/assets/AssetManager.cpp
        include/assets/AssetManager.h
        src/graphics/RenderSystem.cpp
        include/graphics/RenderSystem.h
        src/utils/Logger.cpp
        src/utils/Logger.h
        src/utils/Time.cpp
        include/utils/Time.h
        include/graphics/Shader.h
        src/assets/ShaderManager.cpp
        include/assets/ShaderManager.h
        src/graphics/Material.cpp
        include/graphics/Material.h
)

target_include_directories(Obsidium PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_include_directories(Obsidium PRIVATE thirdparty)

enable_testing()

add_subdirectory(sandbox)


target_compile_definitions(Obsidium PUBLIC VULKAN_HPP_NO_STRUCT_CONSTRUCTORS)

target_link_libraries(Obsidium
        Vulkan::Vulkan
        glfw
        slang
        stbi
)