cmake_minimum_required(VERSION 3.22.1)

project(desktop-sort-app)

set(CMAKE_CXX STANDARD 11)
set(CMAKE_CXX_STANDARD_REQIRED True)

include_directories(glad/include)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

add_subdirectory(glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw)

add_library(glad glad/src/glad.c)
target_link_libraries(${CMAKE_PROJECT_NAME} glad)