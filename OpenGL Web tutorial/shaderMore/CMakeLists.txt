cmake_minimum_required(VERSION 3.14)
project(shaderMore)

set(CMAKE_CXX_STANDARD 17)

add_executable(shaderMore main.cpp glad.c Shader.cpp Shader.h init.cpp init.h)

target_link_libraries(shaderMore glfw3 opengl32 winmm gdi32 glu32.lib )