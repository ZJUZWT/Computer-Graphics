cmake_minimum_required(VERSION 3.14)
project(project4_5_4lerpAnime)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D FREEGLUT_STATIC")

add_executable(project4_5_4lerpAnime main.cpp)
target_link_libraries(project4_5_4lerpAnime freeglut_static opengl32 winmm gdi32 glu32.lib )