#pragma once

#include "Mocca/renderer/render_feature.h"
#include "Mocca/vulkan/commands/frame_manager.h"

#include <memory>
#include <vector>


class Swapchain;
class Pipeline;
class Context; // forward dec
class Window;

class Renderer
{
public:
    Renderer(const Context& context, const Window& window);
    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    void pushFeature(std::unique_ptr<RenderFeature> feature);

    void drawFrame();

private:
    const Context& m_context;
    std::unique_ptr<Swapchain> m_swapchain;

    FrameManager m_frameManager;
    std::vector<std::unique_ptr<RenderFeature>> m_features;
};