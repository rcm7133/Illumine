#pragma once
#include "pch.h"

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

const std::vector<char const*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

/**
 * @brief Core Vulkan application class.
 *
 * Manages the lifetime of all Vulkan and GLFW resources.
 * Initialization order matters, Vulkan objects must be destroyed
 * in reverse order of creation, which is handled automatically via RAII.
 */
class IllumineApplication {
public:
    /**
     * @brief API Entry point. Runs the full app lifecycle.
     */
    void Run();

private:
    // -- Member Variables --
    GLFWwindow* window = nullptr;

    vk::raii::Instance instance = nullptr;
    vk::raii::Context context;
    vk::raii::PhysicalDevice physicalDevice = nullptr;
    vk::raii::Device device = nullptr;
    std::vector<const char*> requiredDeviceExtension = {vk::KHRSwapchainExtensionName};
    vk::raii::Queue graphicsQueue = nullptr;
    // -- Initialization --
    void InitWindow();
    void InitVulkan();
    void CreateVulkanInstance();
    // -- Device Creation
    void PickPhysicalDevice();
    void CreateLogicalDevice();
    // -- Main Logic --
    void MainLoop();
    // -- Clean up --
    void Cleanup();
    // -- Helper Functions
    std::vector<const char*> GetRequiredInstanceExtensions();
    /**
     * @brief Checks if a physical device meets all rendering requirements.
     *
     * Requires: Vulkan 1.3+, graphics queue, swapchain extension,
     * dynamic rendering, and extended dynamic state features.
     */
    bool IsDeviceSuitable( vk::raii::PhysicalDevice const & physicalDevice);
};