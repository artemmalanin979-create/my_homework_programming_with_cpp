cmake_minimum_required(VERSION 3.16)
project(DragonCXX LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS   OFF)

# --------- FLTK ----------
find_package(FLTK 1.3.8 EXACT REQUIRED)
find_package(OpenGL REQUIRED)

# --------- наши файлы ----
set(HEADERS include/Dragon.h)
set(SOURCES src/main.cpp src/Dragon.cpp)

add_executable(dragon ${SOURCES} ${HEADERS})

target_include_directories(dragon PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${FLTK_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR})

target_link_libraries(dragon
    ${FLTK_LIBRARIES}
    ${OPENGL_LIBRARIES})