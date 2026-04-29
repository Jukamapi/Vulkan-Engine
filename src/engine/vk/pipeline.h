#pragma once

#include <volk/volk.h>
#include <vector>

class Swapchain;

class Pipeline
{
public:
    Pipeline(const Swapchain& swapchain, VkDevice device);
    ~Pipeline();

    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;
    Pipeline(Pipeline&&) = delete;
    Pipeline& operator=(Pipeline&&) = delete;

private:
    VkPipelineLayout m_pipelineLayout{ VK_NULL_HANDLE };
    VkPipeline m_pipeline{ VK_NULL_HANDLE };
    VkDevice m_device{ VK_NULL_HANDLE };

    std::vector<VkDynamicState> m_dynamicStates{
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
    };

    VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice device) const;
};