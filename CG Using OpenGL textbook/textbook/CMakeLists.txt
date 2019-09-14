cmake_minimum_required(VERSION 3.14)
project(textbook)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D FREEGLUT_STATIC")

add_executable(textbook main.cpp)
target_link_libraries(textbook freeglut_static opengl32 winmm gdi32 glu32.lib )