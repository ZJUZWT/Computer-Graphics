//
// Created by MrKill on 2019/9/13.
//

#ifndef SHADERMORE_SHADER_H
#define SHADERMORE_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
public:
    unsigned int id ;

    Shader(const GLchar* vertexShaderName,const GLchar* fragmentShaderName) ;

    void use() ;
};


#endif //SHADERMORE_SHADER_H
