cmake_minimum_required(VERSION 3.14)
project(project5_5_2hexDraw)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D FREEGLUT_STATIC")

add_executable(project5_5_2hexDraw main.cpp )
target_link_libraries(project5_5_2hexDraw freeglut_static opengl32 winmm gdi32 glu32.lib )