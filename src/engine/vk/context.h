#pragma once

#include "engine/vk/instance.h"
#include "engine/vk/surface.h"
#include "engine/vk/physical_device.h"
#include "engine/vk/logical_device.h"

#include <volk.h>

class Window;

class Context
{
public:
    Context(Window& window);
    ~Context();
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(Context&&) = delete;


    VkInstance getInstanceHandle() const { return m_instance.getHandle(); }
    VkDevice getDeviceHandle() const { return m_logicalDevice.getHandle(); }
    VkSurfaceKHR getSurfaceHandle() const { return m_surface.getHandle(); }
    const PhysicalDevice& getPhysicalDevice() const { return m_physicalDevice; }

private:
    Instance m_instance;
    Surface m_surface;
    PhysicalDevice m_physicalDevice;
    LogicalDevice m_logicalDevice;
};