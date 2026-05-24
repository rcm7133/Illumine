cmake_minimum_required(VERSION 3.10...3.31)

project(Illumine VERSION 1.0)

if (UNIX AND NOT APPLE)
    cmake_policy(SET CMP0072 NEW)
endif()

file(TO_CMAKE_PATH "$ENV{VULKAN_SDK}" VULKAN_SDK_PATH)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)

add_executable(Illumine
        src/main.cpp
        # --- Dependencies ---
        # ImGUI
        dependencies/imgui/imgui.cpp
        dependencies/imgui/imgui_draw.cpp
        dependencies/imgui/imgui_tables.cpp
        dependencies/imgui/imgui_widgets.cpp
        dependencies/imgui/imgui_impl_glfw.cpp
        dependencies/imgui/imgui_impl_vulkan.cpp
)

target_include_directories(Illumine PRIVATE
        src
        dependencies
        dependencies/imgui
        dependencies/stbimage
        "${VULKAN_SDK_PATH}/Include"
)

target_link_libraries(Illumine PRIVATE
        Vulkan::Vulkan
        glfw
        glm::glm
        tinyobjloader::tinyobjloader
)

target_precompile_headers(Illumine PRIVATE src/pch.h)
target_compile_features(Illumine PRIVATE cxx_std_23)

# Disable PCH for imgui files
set_source_files_properties(
        dependencies/imgui/imgui.cpp
        dependencies/imgui/imgui_draw.cpp
        dependencies/imgui/imgui_tables.cpp
        dependencies/imgui/imgui_widgets.cpp
        dependencies/imgui/imgui_impl_glfw.cpp
        dependencies/imgui/imgui_impl_vulkan.cpp
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)

if(UNIX)
    target_link_libraries(Illumine PRIVATE dl)
endif()

if(WIN32)
    target_link_libraries(Illumine PRIVATE gdi32 user32)
endif()