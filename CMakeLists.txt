cmake_minimum_required(VERSION 3.10...3.31)

project(Illumine VERSION 1.0)

if (UNIX AND NOT APPLE)
    cmake_policy(SET CMP0072)
endif()

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(Illumine
        src/main.cpp
)

target_include_directories(Illumine PRIVATE
    src
    dependencies
    dependencies/imgui
)

target_link_libraries(Illumine PRIVATE
        glfw
        glm::glm
)

target_compile_features(Illumine PRIVATE cxx_std_23)

if(UNIX)
    target_link_libraries(Illumine PRIVATE dl)
endif()

if(WIN32)
    target_link_libraries(Illumine PRIVATE gdi32 user32)
endif()