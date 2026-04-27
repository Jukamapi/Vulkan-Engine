#include "context.h"

#include "engine/window/window.h"

Context::Context(Window& window)
    : m_instance(window.getAppName(), window.getExtensions()),
    m_surface(window.getNativeWindow(), m_instance.getHandle()),
    m_physicalDevice(m_instance.getHandle(), m_surface.getHandle()),
    m_logicalDevice(m_physicalDevice)
{
    // initialize instance
    // initialize physical device
    // logical device etc.
}

Context::~Context()
{

}