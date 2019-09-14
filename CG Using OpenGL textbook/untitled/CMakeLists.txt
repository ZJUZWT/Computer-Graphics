cmake_minimum_required(VERSION 3.14)
project(OpenGL_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D FREEGLUT_STATIC")

add_executable(OpenGL_3 main.cpp)
target_link_libraries(OpenGL_3 freeglut_static opengl32 winmm gdi32 glu32.lib )