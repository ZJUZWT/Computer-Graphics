//
// Created by MrKill on 2019/9/13.
//
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const GLchar *vertexShaderName, const GLchar *fragmentShaderName) {

    std::string vertexShaderCode ;
    std::string fragmentShaderCode ;
    std::ifstream vShaderFile ;
    std::ifstream fShaderFile ;

    vShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit ) ;
    fShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit ) ;
    try {
        vShaderFile.open(vertexShaderName) ;
        fShaderFile.open(fragmentShaderName) ;

        std::stringstream vShaderStream ;
        std::stringstream fShaderStream ;

        vShaderStream << vShaderFile.rdbuf() ;
        fShaderStream << fShaderFile.rdbuf() ;

        vShaderFile.close() ;
        fShaderFile.close() ;

        vertexShaderCode = vShaderStream.str() ;
        fragmentShaderCode = fShaderStream.str() ;
    } catch( std::ifstream::failure e ) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    int success ;
    char infoLog[512] ;

    const char *vertexShaderSource = vertexShaderCode.c_str() ;
    const char *fragmentShaderSource = fragmentShaderCode.c_str() ;

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER) ;
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER) ;

    glShaderSource(vertexShader,1,&vertexShaderSource,nullptr) ;
    glShaderSource(fragmentShader,1,&fragmentShaderSource,nullptr) ;

    glCompileShader(vertexShader) ;
    glCompileShader(fragmentShader) ;

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success) ;
    if ( !success ) {
        glGetShaderInfoLog(vertexShader,512,nullptr,infoLog) ;
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success) ;
    if ( !success ) {
        glGetShaderInfoLog(fragmentShader,512,nullptr,infoLog) ;
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    this->id = glCreateProgram() ;
    glAttachShader(id,vertexShader) ;
    glAttachShader(id,fragmentShader) ;
    glLinkProgram(id) ;

    glGetProgramiv(id,GL_LINK_STATUS,&success) ;
    if ( !success ) {
        glGetProgramInfoLog(id,512,nullptr,infoLog) ;
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader) ;
    glDeleteShader(fragmentShader) ;
}

void Shader::use() {
    glUseProgram(this->id) ;
}