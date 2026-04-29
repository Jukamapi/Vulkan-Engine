#include "renderer.h"

#include "engine/vk/physical_device.h"
#include "engine/vk/context.h"
#include "engine/window/window.h"

Renderer::Renderer(const Context& context, const Window& window)
    : m_swapchain(context.getPhysicalDevice(), context.getDeviceHandle(), context.getSurfaceHandle(), window.getDrawableSize()),
    m_pipeline(m_swapchain, context.getDeviceHandle()),
    m_frameManager()
{
}

//const PhysicalDevice& physicalDevice, VkDevice device, VkSurfaceKHR surface, uint32_t drawableWidth, uint32_t drawableHeight


void Renderer::drawFrame()
{
    //  wait for fence
    //  currentFrame.deletionQueue.flush();
    //  reset fence

    //  start rendering
    //  execute all features in order
    // for (auto& feature : m_features)
}

void Renderer::pushFeature(std::unique_ptr<RenderFeature> feature)
{
    feature->onAttach();
    m_features.push_back(std::move(feature));
}

Renderer::~Renderer()
{
    //  detach features
    //
}