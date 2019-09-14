cmake_minimum_required(VERSION 3.14)
project(jewTest)

set(CMAKE_CXX_STANDARD 14)

add_executable(jewTest main.cpp)

target_link_libraries(jewTest freeglutstatic glfw opengl32 winmm gdi32 glu32.lib )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D FREEGLUT_STATIC")
