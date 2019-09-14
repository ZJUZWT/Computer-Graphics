cmake_minimum_required(VERSION 3.14)
project(project6_2_3vnTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D FREEGLUT_STATIC")

add_executable(project6_2_3vnTest main.cpp SDL.cpp)
target_link_libraries(project6_2_3vnTest freeglut_static opengl32 winmm gdi32 glu32.lib )