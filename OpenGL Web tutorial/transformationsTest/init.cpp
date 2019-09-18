//
// Created by MrKill on 2019/9/13.
//

#include <iostream>
#include "init.h"

bool checkGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load GLAD" << std::endl ;
        return false ;
    }
    return true ;
}

bool checkWindows(GLFWwindow* window) {
    if ( window == nullptr ) {
        std::cout<< "Failed to open window" << std::endl ;
        glfwTerminate() ;
        return false;
    }
    glfwMakeContextCurrent(window) ;
    return true ;
}

void myStartInit() {
    glfwInit() ;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3) ;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3) ;
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE) ;
}

void myLoopInit() {
    glClearColor(0.5f,0.5f,0.5f,1.0f) ;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT) ;
}