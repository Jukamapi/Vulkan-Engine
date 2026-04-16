#pragma once

#include <variant>
#include <cstdint>

struct WindowCloseEvent {};

struct WindowResizeEvent
{
    uint32_t width;
    uint32_t height;
};

struct MouseMoveEvent
{
    int32_t x;
    int32_t y;
};

using Event = std::variant<
    WindowCloseEvent,
    WindowResizeEvent,
    MouseMoveEvent
>;
