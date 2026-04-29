#include "frame_manager.h"

#include "Mocca/vulkan/commands/command_pool.h"
#include "Mocca/vulkan/core/physical_device.h"
#include "Mocca/vulkan/vulkan_utils.h"


FrameManager::FrameManager(const PhysicalDevice& physicalDevice, VkDevice device) : m_device(device)
{
    try
    {
    }
    catch(...)
    {
        for(int i = 0; i < 2; i++)
        {
            if(m_frames[i].imageAvailableSemaphore)
            {
                vkDestroySemaphore(m_device, m_frames[i].imageAvailableSemaphore, nullptr);
            }
            if(m_frames[i].renderFinishedSemaphore)
            {
                vkDestroySemaphore(m_device, m_frames[i].renderFinishedSemaphore, nullptr);
            }
            if(m_frames[i].renderFence)
            {
                vkDestroyFence(m_device, m_frames[i].renderFence, nullptr);
            }
        }

        throw;
    }

    for(int i = 0; i < 2; i++)
    {
        m_frames[i].commandPool = std::make_unique<CommandPool>(physicalDevice, m_device);

        auto buffers = m_frames[i].commandPool->allocateBuffers(1);
        m_frames[i].commandBuffer = buffers[0];

        VkSemaphoreCreateInfo semaphoreInfo{
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        };

        VkFenceCreateInfo fenceInfo{
            .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            .flags = VK_FENCE_CREATE_SIGNALED_BIT,
            // start signaled
        };

        VK_CHECK(vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_frames[i].imageAvailableSemaphore));

        VK_CHECK(vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_frames[i].renderFinishedSemaphore));

        VK_CHECK(vkCreateFence(m_device, &fenceInfo, nullptr, &m_frames[i].renderFence));
    }
}

void FrameManager::advance()
{
    m_currentFrameIndex = (m_currentFrameIndex + 1) % 2;
}

FrameManager::~FrameManager()
{
    for(int i = 0; i < 2; i++)
    {
        vkDestroySemaphore(m_device, m_frames[i].imageAvailableSemaphore, nullptr);
        vkDestroySemaphore(m_device, m_frames[i].renderFinishedSemaphore, nullptr);
        vkDestroyFence(m_device, m_frames[i].renderFence, nullptr);
        // commandPool is unique_ptr so destructor called automatically
    }
}