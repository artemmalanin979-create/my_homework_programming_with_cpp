cmake_minimum_required(VERSION 3.10)   # C++17 достаточно 3.10+
project(Angle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(angle INTERFACE)
add_library(angle::angle ALIAS angle)
target_include_directories(angle INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

add_executable(example example/main.cpp)
target_link_libraries(example PRIVATE angle::angle)