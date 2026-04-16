#pragma once

#include "engine/vk/deletion_queue.h"
#include <vulkan/vulkan.h>

class Window;

class Context
{
public:
    // .getNativeWindow() to create the surface
    Context(Window& window);
    ~Context();
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(Context&&) = delete;

    uint32_t getWindowWidth() const;
    uint32_t getWindowHeight() const;

    //  todo: getters for vulkan specific
    VkDevice getDevice() const { return m_device; }

    // might modiffy


private:
    Window& m_window;

    // todo: instance, device
    VkDevice m_device{};
};