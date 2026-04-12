include(FetchContent)

find_package(Vulkan REQUIRED)

find_package(SDL2 QUIET)

if(NOT SDL2_FOUND)
    message(STATUS "SDL2 not found, fetching...")

    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.28.x
    )

    set(SDL_SHARED OFF CACHE BOOL "" FORCE)
    set(SDL_STATIC ON CACHE BOOL "" FORCE)
    set(SDL_TEST OFF CACHE BOOL "" FORCE)

    set(SDL_AUDIO OFF CACHE BOOL "" FORCE)
    set(SDL_RENDER OFF CACHE BOOL "" FORCE)
    set(SDL_JOYSTICK OFF CACHE BOOL "" FORCE)
    set(SDL_HAPTIC OFF CACHE BOOL "" FORCE)
    set(SDL_SENSOR OFF CACHE BOOL "" FORCE)
    set(SDL_OPENGL OFF CACHE BOOL "" FORCE)
    set(SDL_OPENGLES OFF CACHE BOOL "" FORCE)

    set(SDL_VIDEO ON CACHE BOOL "" FORCE)
    set(SDL_EVENTS ON CACHE BOOL "" FORCE)
    set(SDL_THREADS ON CACHE BOOL "" FORCE)
    set(SDL_TIMERS ON CACHE BOOL "" FORCE)
    set(SDL_VULKAN ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(SDL2)
endif()

FetchContent_Declare(
    fastgltf
    GIT_REPOSITORY https://github.com/spnda/fastgltf.git
    GIT_TAG v0.7.2
)

FetchContent_MakeAvailable(fastgltf)

add_library(volk STATIC vendor/volk/volk.c)

target_include_directories(volk PUBLIC vendor/volk)

target_link_libraries(volk PUBLIC Vulkan::Vulkan)