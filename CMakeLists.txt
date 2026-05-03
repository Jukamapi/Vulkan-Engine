cmake_minimum_required(VERSION 3.20)
project(Mocca LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

#for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

add_subdirectory(src/Mocca)
add_subdirectory(src/Sandbox)

target_compile_definitions(volk PUBLIC VK_NO_PROTOTYPES)
target_compile_definitions(mocca PUBLIC VK_NO_PROTOTYPES)
target_compile_definitions(imgui PUBLIC VK_NO_PROTOTYPES)

target_compile_definitions(mocca PUBLIC SHADER_DIR="${SPIRV_DIR}")