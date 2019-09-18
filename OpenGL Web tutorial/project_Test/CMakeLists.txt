cmake_minimum_required(VERSION 3.14)
project(project_Test)

set(CMAKE_CXX_STANDARD 17)

add_executable(project_Test main.cpp glad.c)

target_link_libraries(project_Test glfw3 opengl32 winmm gdi32 glu32.lib )