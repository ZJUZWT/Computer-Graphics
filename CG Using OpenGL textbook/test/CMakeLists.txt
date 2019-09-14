cmake_minimum_required(VERSION 3.14)
project(test)

#INCLUDE_DIRECTORIES("C:/MinGW/include")
#link_directories("C:/MinGW/lib")

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D FREEGLUT_STATIC")

add_executable(test main.cpp)
target_link_libraries(test freeglut_static opengl32 winmm gdi32 glu32.lib)