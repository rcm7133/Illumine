cmake_minimum_required(VERSION 3.10...3.31)

project(Illumine VERSION 1.0)

if (UNIX AND NOT APPLE)
    cmake_policy(SET CMP0072 NEW)
endif()


file(TO_CMAKE_PATH "$ENV{VULKAN_SDK}" VULKAN_SDK_PATH)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(Illumine
        src/main.cpp
)

target_include_directories(Illumine PRIVATE
        src
        dependencies
        "${VULKAN_SDK_PATH}/Include"
)

target_link_libraries(Illumine PRIVATE
        Vulkan::Vulkan
        glfw
        glm::glm
)

target_precompile_headers(Illumine PRIVATE src/pch.h)
target_compile_features(Illumine PRIVATE cxx_std_23)

if(UNIX)
    target_link_libraries(Illumine PRIVATE dl)
endif()

if(WIN32)
    target_link_libraries(Illumine PRIVATE gdi32 user32)
endif()