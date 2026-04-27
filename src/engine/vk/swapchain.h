#pragma once

#include <volk/volk.h>
#include <vector>

class PhysicalDevice;
struct Extent;

class Swapchain
{
public:
    Swapchain(const PhysicalDevice& physicalDevice, VkDevice device, VkSurfaceKHR surface, Extent frameBufferSize);
    ~Swapchain();

    //TODO: change this to be allocated on the heap maybe as it needs to be recreated

    Swapchain(const Swapchain&) = delete;
    Swapchain& operator=(const Swapchain&) = delete;
    Swapchain(Swapchain&&) = delete;
    Swapchain& operator=(Swapchain&&) = delete;

    // struct SwapChainSupportDetails <----- in physical_device for querying
    // {
    //     VkSurfaceCapabilitiesKHR capabilities;
    //     std::vector<VkSurfaceFormatKHR> formats;
    //     std::vector<VkPresentModeKHR> presentModes;
    // };


private:
    VkSwapchainKHR m_swapchain{ VK_NULL_HANDLE };
    VkDevice m_logicalDevice{ VK_NULL_HANDLE };
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainExtent;
    std::vector<VkImage> m_swapChainImages;

    //helpers
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) const;
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const;
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, uint32_t windowWidth, uint32_t windowHeight) const;
};