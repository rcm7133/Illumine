cmake_minimum_required(VERSION 3.10...3.31)

project(Illumine VERSION 1.0)

if (UNIX AND NOT APPLE)
    cmake_policy(SET CMP0072 NEW)
endif()

file(TO_CMAKE_PATH "$ENV{VULKAN_SDK}" VULKAN_SDK_PATH)

find_program(GLSLC_EXECUTABLE
        NAMES glslc glslc.exe
        HINTS "${VULKAN_SDK_PATH}/bin"
        REQUIRED
)
message(STATUS "Found glslc: ${GLSLC_EXECUTABLE}")


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
        src/IllumineApplication.cpp
        src/utils.cpp
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

# Shader compilation
set(VERT_SHADER ${CMAKE_CURRENT_LIST_DIR}/shaders/src/shader.vert)
set(FRAG_SHADER ${CMAKE_CURRENT_LIST_DIR}/shaders/src/shader.frag)
set(VERT_SPV ${CMAKE_CURRENT_LIST_DIR}/shaders/compiled/vert.spv)
set(FRAG_SPV ${CMAKE_CURRENT_LIST_DIR}/shaders/compiled/frag.spv)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/shaders/compiled)

add_custom_command(
        OUTPUT ${VERT_SPV}
        COMMAND ${GLSLC_EXECUTABLE} ${VERT_SHADER} -o ${VERT_SPV}
        DEPENDS ${VERT_SHADER}
        COMMENT "Compiling vertex shader"
        VERBATIM
)

add_custom_command(
        OUTPUT ${FRAG_SPV}
        COMMAND ${GLSLC_EXECUTABLE} ${FRAG_SHADER} -o ${FRAG_SPV}
        DEPENDS ${FRAG_SHADER}
        COMMENT "Compiling fragment shader"
        VERBATIM
)

add_custom_target(IllumineShaders DEPENDS ${VERT_SPV} ${FRAG_SPV})
add_dependencies(Illumine IllumineShaders)