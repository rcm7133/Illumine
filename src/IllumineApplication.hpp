#pragma once
#include "pch.h"

constexpr uint32_t WIDTH = 1920;
constexpr uint32_t HEIGHT = 1080;

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
    // Member Variables
    GLFWwindow* window = nullptr;

    vk::raii::Instance instance = nullptr;
    vk::raii::Context context;
    vk::raii::PhysicalDevice physicalDevice = nullptr;
    vk::raii::Device device = nullptr;
    std::vector<const char*> requiredDeviceExtension = {vk::KHRSwapchainExtensionName};
    vk::raii::Queue graphicsQueue = nullptr;
    uint32_t queueIndex = ~0;
    vk::raii::SurfaceKHR surface = nullptr;
    vk::raii::SwapchainKHR swapChain = nullptr;
    std::vector<vk::Image> swapChainImages;
    vk::SurfaceFormatKHR swapChainSurfaceFormat;
    vk::Extent2D swapChainExtent;
    std::vector<vk::raii::ImageView> swapChainImageViews;
    vk::raii::Pipeline graphicsPipeline = nullptr;
    vk::raii::CommandPool commandPool = nullptr;
    vk::raii::CommandBuffer commandBuffer = nullptr;
    // Sync objects
    vk::raii::Semaphore presentCompleteSemaphore = nullptr;
    vk::raii::Semaphore renderFinishedSemaphore = nullptr;
    vk::raii::Fence drawFence = nullptr;

    // Initialization
    void InitWindow();
    void InitVulkan();
    void CreateVulkanInstance();
    void CreateSurface();
    void CreateSwapChain();
    void CreateImageViews();
    void CreateGraphicsPipeline();
    void CreateSyncObjects();
    // Device Creation
    void PickPhysicalDevice();
    void CreateLogicalDevice();
    // Shaders
    [[nodiscard]] vk::raii::ShaderModule CreateShaderModule(std::vector<char> const &code) const;
    // Commands
    void CreateCommandPool();
    void CreateCommandBuffer();
    void RecordCommandBuffer(uint32_t imageIndex);
    // Main Logic
    void MainLoop();
    void DrawFrame();
    // Clean up
    void Cleanup();
    // Helper Functions
    std::vector<const char*> GetRequiredInstanceExtensions();
    void TransitionImageLayout(uint32_t, vk::ImageLayout, vk::ImageLayout, vk::AccessFlags2, vk::AccessFlags2, vk::PipelineStageFlags2,vk::PipelineStageFlags2);
    /**
     * @brief Checks if a physical device meets all rendering requirements.
     *
     * Requires: Vulkan 1.3+, graphics queue, swap chain extension,
     * dynamic rendering, and extended dynamic state features.
     */
    bool IsDeviceSuitable( vk::raii::PhysicalDevice const & physicalDevice);

    vk::SurfaceFormatKHR ChooseSwapSurfaceFormat(std::vector<vk::SurfaceFormatKHR> const &);
    vk::PresentModeKHR ChooseSwapPresentMode(std::vector<vk::PresentModeKHR> const &);
    vk::Extent2D ChooseSwapExtent(vk::SurfaceCapabilitiesKHR const &capabilities);
    uint32_t ChooseSwapMinImageCount(vk::SurfaceCapabilitiesKHR const &surfaceCapabilities);
};