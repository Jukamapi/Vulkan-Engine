#pragma once

#include <cstdint>
#include <vulkan/vulkan_core.h>
#include <optional>

class Context;

class PhysicalDevice
{
public:
    PhysicalDevice(VkInstance instance);
    ~PhysicalDevice();
    PhysicalDevice(PhysicalDevice&) = delete;
    PhysicalDevice& operator=(PhysicalDevice&) = delete;
    PhysicalDevice(PhysicalDevice&&) = delete;
    PhysicalDevice& operator=(PhysicalDevice&&) = delete;

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value();
        }
    };

    void pickPhysicalDevice(VkInstance instance);
    int rateDeviceSuitability(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

private:
    VkPhysicalDevice m_physicalDevice{};
    QueueFamilyIndices m_familyIndices;
};