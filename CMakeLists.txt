cmake_minimum_required(VERSION 3.20)
project(VulkanEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#options
option(ENGINE_BUILD_EDITOR "Build editor module" ON)
option(ENGINE_ENABLE_VALIDATION "Enable Vulkan validation layers" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(dependencies)
include(imgui)
include(shaders)

#vendor headers
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE vendor/glm)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE vendor/stb)

add_library(vma INTERFACE)
target_include_directories(vma INTERFACE vendor/vma)

#engine
add_library(engine STATIC
    src/engine/core/application.cpp
    src/engine/core/window.cpp
    src/engine/core/logger.cpp

    src/engine/vulkan/vulkan_context.cpp
    src/engine/vulkan/vulkan_swapchain.cpp
    src/engine/vulkan/vulkan_buffer.cpp
    src/engine/vulkan/vulkan_image.cpp
    src/engine/vulkan/vulkan_pipeline.cpp
    src/engine/vulkan/vulkan_descriptors.cpp

    src/engine/renderer/renderer.cpp
    src/engine/renderer/scene.cpp

    src/engine/resources/loader.cpp
)

target_include_directories(engine PUBLIC src)

target_link_libraries(engine PUBLIC
    Vulkan::Vulkan
    SDL2::SDL2
    fastgltf
    volk
    glm
    stb
    vma
)

#optional editor
if(ENGINE_BUILD_EDITOR)
    add_library(editor STATIC
        src/editor/editor_ui.cpp
    )

    target_link_libraries(editor PUBLIC engine imgui)
endif()

#app
add_executable(app src/main.cpp)

target_compile_definitions(app PRIVATE SDL_MAIN_HANDLED)

target_link_libraries(app PRIVATE
    engine
    SDL2::SDL2
)

if(ENGINE_BUILD_EDITOR)
    target_link_libraries(app PRIVATE editor)
endif()

#shader
add_dependencies(app shaders)