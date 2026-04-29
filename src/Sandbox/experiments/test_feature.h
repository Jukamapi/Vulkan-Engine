#pragma once

#include "Mocca/renderer/render_feature.h"
#include "Mocca/vulkan/pipeline/pipeline.h"
#include <memory>


class testFeature : public RenderFeature
{
public:
    void onAttach(VkDevice device, VkFormat colorFormat, VkExtent2D extent) override
    {
        m_pipeline = std::make_unique<Pipeline>(
            device,
            colorFormat,
            extent,
            "../build/shaders/triangle.vert.spv",
            "../build/shaders/triangle.frag.spv"
        );
    }
    void onRender(VkCommandBuffer cmd) override
    {
        vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline->getHandle());

        vkCmdDraw(cmd, 3, 1, 0, 0);
    }

private:
    std::unique_ptr<Pipeline> m_pipeline;
};