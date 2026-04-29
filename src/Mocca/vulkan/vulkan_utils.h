#pragma once

#include <source_location>
#include <volk/volk.h>


void vk_check_impl(VkResult result, const char* expression, std::source_location loc = std::source_location::current());

#define VK_CHECK(x) vk_check_impl(x, #x)