cmake_minimum_required(VERSION 3.14)
project(colorBuildTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(colorBuildTest main.cpp glad.c Shader.cpp Shader.h init.cpp init.h LoadElement.cpp LoadElement.h)

target_link_libraries(colorBuildTest glfw3 opengl32 winmm gdi32 glu32.lib )