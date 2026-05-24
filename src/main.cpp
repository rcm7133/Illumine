#include "pch.h"

int main()
{
    uint32_t version;
    vkEnumerateInstanceVersion(&version);
    std::cout << "Vulkan version: "
              << VK_VERSION_MAJOR(version) << "."
              << VK_VERSION_MINOR(version) << "."
              << VK_VERSION_PATCH(version) << "\n";
    return 0;
}