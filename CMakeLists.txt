cmake_minimum_required(VERSION 3.20)
project(Mocca LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

#for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(VK_NO_PROTOTYPES)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(dependencies)
include(imgui)
include(shaders)

#vendor
add_library(volk STATIC vendor/volk/volk.c)
target_link_libraries(volk PUBLIC Vulkan::Headers)
target_include_directories(volk PUBLIC vendor/volk)
if(UNIX)
    target_link_libraries(volk PRIVATE dl)
endif()

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE vendor)
target_compile_definitions(glm INTERFACE
    GLM_FORCE_RADIANS
    GLM_FORCE_DEPTH_ZERO_TO_ONE
)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE vendor)

add_library(vma INTERFACE)
target_include_directories(vma INTERFACE vendor)

#mocca library
add_library(mocca STATIC)

target_sources(mocca PRIVATE
    #core
    src/Mocca/core/application.cpp
    src/Mocca/core/window.cpp

    #vulkan backend
    src/Mocca/vulkan/core/context.cpp
    src/Mocca/vulkan/core/instance.cpp
    src/Mocca/vulkan/core/physical_device.cpp
    src/Mocca/vulkan/core/logical_device.cpp
    src/Mocca/vulkan/core/surface.cpp
    src/Mocca/vulkan/vulkan_utils.cpp
    src/Mocca/vulkan/resources/swapchain.cpp
    src/Mocca/vulkan/pipeline/pipeline.cpp
    src/Mocca/vulkan/commands/command_pool.cpp
    src/Mocca/vulkan/commands/frame_manager.cpp

    #renderer logic
    src/Mocca/renderer/renderer.cpp

    #vndor init logic
    vendor/vendor_init.cpp
)

target_sources(mocca PUBLIC
    FILE_SET HEADERS
    BASE_DIRS src
    FILES
        #core
        src/Mocca/core/application.h
        src/Mocca/core/event.h
        src/Mocca/core/input.h
        src/Mocca/core/types.h
        src/Mocca/core/window.h

        #vulkan core
        src/Mocca/vulkan/core/context.h
        src/Mocca/vulkan/core/instance.h
        src/Mocca/vulkan/core/physical_device.h
        src/Mocca/vulkan/core/logical_device.h
        src/Mocca/vulkan/core/surface.h

        #vulkan resources
        src/Mocca/vulkan/vulkan_utils.h
        src/Mocca/vulkan/resources/swapchain.h
        src/Mocca/vulkan/pipeline/pipeline.h
        src/Mocca/vulkan/commands/command_pool.h
        src/Mocca/vulkan/commands/frame_manager.h
        src/Mocca/vulkan/commands/deletion_queue.h

        src/Mocca/resources/loader.h
        src/Mocca/renderer/renderer.h
        src/Mocca/renderer/render_feature.h
)

target_include_directories(mocca PUBLIC src)

target_link_libraries(mocca PUBLIC
    volk
    SDL2::SDL2
    fastgltf
    glm
    stb
    vma
)

#sandbox-app
add_executable(sandbox src/Sandbox/main.cpp)
set_target_properties(sandbox PROPERTIES WIN32_EXECUTABLE FALSE)

target_compile_definitions(sandbox PRIVATE SDL_MAIN_HANDLED)

target_link_libraries(sandbox PRIVATE
    mocca
    SDL2::SDL2
)

add_dependencies(sandbox shaders)