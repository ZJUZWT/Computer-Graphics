cmake_minimum_required(VERSION 3.14)
project(project4_6_1circleByPoints)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D FREEGLUT_STATIC")

add_executable(project4_6_1circleByPoints main.cpp Coordinate.cpp Coordinate.h Point.cpp)
target_link_libraries(project4_6_1circleByPoints freeglut_static opengl32 winmm gdi32 glu32.lib )