#pragma once

#include "engine/renderer/render_feature.h"
#include "engine/vk/frame_manager.h"
#include "engine/vk/swapchain.h"
#include "engine/vk/pipeline.h"

#include <vector>
#include <memory>


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
    Swapchain m_swapchain;
    Pipeline m_pipeline;

    FrameManager m_frameManager;
    std::vector<std::unique_ptr<RenderFeature>> m_features;
};