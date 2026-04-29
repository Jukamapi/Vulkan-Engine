#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include <volk.h>


class Context;

class PhysicalDevice
{
public:
    PhysicalDevice(VkInstance instance, VkSurfaceKHR surface);
    ~PhysicalDevice() = default;
    PhysicalDevice(PhysicalDevice&) = delete;
    PhysicalDevice& operator=(PhysicalDevice&) = delete;
    PhysicalDevice(PhysicalDevice&&) = delete;
    PhysicalDevice& operator=(PhysicalDevice&&) = delete;

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    VkPhysicalDevice getPhysicalDeviceHandle() const
    {
        return m_physicalDevice;
    }
    QueueFamilyIndices getQueueFamilyIndices() const
    {
        return m_familyIndices;
    }
    const std::vector<const char*> getDeviceExtensions() const
    {
        return m_deviceExtensions;
    }
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface) const;


private:
    // helpers
    bool checkDeviceExtensionSupport(VkPhysicalDevice device) const;
    int rateDeviceSuitability(VkPhysicalDevice device, VkSurfaceKHR instance) const;
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) const;


    VkPhysicalDevice m_physicalDevice{VK_NULL_HANDLE};
    QueueFamilyIndices m_familyIndices;

    const std::vector<const char*> m_deviceExtensions{VK_KHR_SWAPCHAIN_EXTENSION_NAME};
};