#pragma once
#include "pch.h"

/**
 * Namespace holding helpful utility functions such as shader module creation, file reading, and more
 */
namespace Utils {
    std::vector<char> ReadFile(const std::string& filename);
    void TransitionImageLayout(uint32_t, vk::ImageLayout, vk::ImageLayout, vk::AccessFlags2, vk::AccessFlags2, vk::PipelineStageFlags2, vk::PipelineStageFlags2);
}