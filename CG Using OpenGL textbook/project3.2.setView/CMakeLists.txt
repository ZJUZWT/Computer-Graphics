cmake_minimum_required(VERSION 3.14)
project(project3_2_setView)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D FREEGLUT_STATIC")

add_executable(project3_2_setView main.cpp)
target_link_libraries(project3_2_setView freeglut_static opengl32 winmm gdi32 glu32.lib )