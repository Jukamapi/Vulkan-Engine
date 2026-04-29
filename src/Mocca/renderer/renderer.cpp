#include "renderer.h"

#include "Mocca/core/window.h"
#include "Mocca/vulkan/commands/command_pool.h"
#include "Mocca/vulkan/core/context.h"
#include "Mocca/vulkan/core/physical_device.h"
#include "Mocca/vulkan/resources/swapchain.h"


Renderer::Renderer(const Context& context, const Window& window)
    : m_context(context), m_frameManager(context.getPhysicalDevice(), context.getLogicalDevice().getHandle())
{
    m_swapchain = std::make_unique<Swapchain>(
        context.getPhysicalDevice(),
        context.getDeviceHandle(),
        context.getSurfaceHandle(),
        window.getDrawableSize()
    );
}

// const PhysicalDevice& physicalDevice, VkDevice device, VkSurfaceKHR surface, uint32_t drawableWidth, uint32_t
// drawableHeight


void Renderer::drawFrame()
{
    FrameManager::FrameData& currentFrame = m_frameManager.getCurrentFrame();

    vkWaitForFences(m_context.getDeviceHandle(), 1, &currentFrame.renderFence, VK_TRUE, UINT64_MAX);

    currentFrame.deletionQueue.flush();

    currentFrame.commandPool->reset();

    vkResetFences(m_context.getDeviceHandle(), 1, &currentFrame.renderFence);

    uint32_t imageIndex;

    vkAcquireNextImageKHR(
        m_context.getDeviceHandle(),
        m_swapchain->getHandle(),
        UINT64_MAX,
        currentFrame.imageAvailableSemaphore,
        VK_NULL_HANDLE,
        &imageIndex
    );

    // vkResetCommandBuffer(currentFrame.commandBuffer, 0);

    VkCommandBufferBeginInfo beginInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    };

    vkBeginCommandBuffer(currentFrame.commandBuffer, &beginInfo);

    // TODO: color attachment and rendering info
    //  and (Transition image layout to COLOR_ATTACHMENT_OPTIMAL...)

    VkRenderingAttachmentInfo attachmentInfo{};
    VkRenderingInfo renderingInfo{};

    vkCmdBeginRendering(currentFrame.commandBuffer, &renderingInfo);

    // feature loop
    for(auto& feature : m_features)
    {
        feature->onRender(currentFrame.commandBuffer);
    }

    vkCmdEndRendering(currentFrame.commandBuffer);

    // (Transition image layout to PRESENT_SRC_KHR...)

    vkEndCommandBuffer(currentFrame.commandBuffer);

    VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    VkSubmitInfo submitInfo{
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &currentFrame.imageAvailableSemaphore,
        .pWaitDstStageMask = &waitStage,
        .commandBufferCount = 1,
        .pCommandBuffers = &currentFrame.commandBuffer,
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = &currentFrame.renderFinishedSemaphore,
    };

    vkQueueSubmit(m_context.getLogicalDevice().getGraphicsQueue(), 1, &submitInfo, currentFrame.renderFence);

    VkSwapchainKHR swapchainLvalue = m_swapchain->getHandle();
    VkPresentInfoKHR presentInfo{
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &currentFrame.renderFinishedSemaphore,
        .swapchainCount = 1,
        .pSwapchains = &swapchainLvalue,
        .pImageIndices = &imageIndex,
    };

    vkQueuePresentKHR(m_context.getLogicalDevice().getPresentQueue(), &presentInfo);

    m_frameManager.advance();
}

void Renderer::pushFeature(std::unique_ptr<RenderFeature> feature)
{
    feature->onAttach(m_context.getDeviceHandle(), m_swapchain->getFormat(), m_swapchain->getExtent());

    m_features.push_back(std::move(feature));
}

Renderer::~Renderer()
{
    //  detach features
    //
}