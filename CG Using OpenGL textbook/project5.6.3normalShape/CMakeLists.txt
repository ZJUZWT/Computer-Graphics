cmake_minimum_required(VERSION 3.14)
project(project5_6_3normalShape)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D FREEGLUT_STATIC")

add_executable(project5_6_3normalShape main.cpp )
target_link_libraries(project5_6_3normalShape freeglut_static opengl32 winmm gdi32 glu32.lib )