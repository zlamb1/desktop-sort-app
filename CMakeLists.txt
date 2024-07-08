cmake_minimum_required(VERSION 3.22.1)

project(desktop-sort-app)

set(CMAKE_CXX STANDARD 11)
set(CMAKE_CXX_STANDARD_REQIRED True)

include_directories(glad/include)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp src/window/glfw_window.cpp src/gl/buf.cpp src/gl/shader.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src)

add_subdirectory(glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw)

add_library(glad glad/src/glad.c)
target_link_libraries(${CMAKE_PROJECT_NAME} glad)

add_subdirectory(vml)
target_link_libraries(${CMAKE_PROJECT_NAME} vml)