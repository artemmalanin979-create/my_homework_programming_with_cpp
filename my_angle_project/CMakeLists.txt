cmake_minimum_required(VERSION 3.14)
project(Angle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------- наша библиотека (header-only) ----------
add_library(angle INTERFACE)
target_include_directories(angle INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

# ---------- GoogleTest (автоматически) ----------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE   # убирает warning CMP0135
)
FetchContent_MakeAvailable(googletest)

# ---------- тесты ----------
add_executable(angle_tests
    test/angle_test.cpp
)
target_link_libraries(angle_tests
    PRIVATE
    angle           # наши заголовки
    GTest::gtest_main
)

# ---------- авто-запуск ----------
include(GoogleTest)
gtest_discover_tests(angle_tests)