#pragma once

#include <volk.h>

#include <vector>

class PhysicalDevice;

class CommandPool
{
public:
    CommandPool(const PhysicalDevice& physicalDevice, VkDevice device);
    ~CommandPool();

    CommandPool(const CommandPool&) = delete;
    CommandPool& operator=(const CommandPool&) = delete;
    CommandPool(CommandPool&&) = delete;
    CommandPool& operator=(CommandPool&&) = delete;

    std::vector<VkCommandBuffer> allocateBuffers(uint32_t count) const;

    void reset() const;

private:
    VkCommandPool m_commandPool{VK_NULL_HANDLE};
    VkDevice m_logicalDevice{VK_NULL_HANDLE};
};