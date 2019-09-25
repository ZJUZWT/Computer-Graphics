//
// Created by MrKill on 2019/9/13.
//

#ifndef _SHADER_H
#define _SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader {
public:
    unsigned int id ;

    Shader(const GLchar* vertexShaderName,const GLchar* fragmentShaderName) ;

    void use() ;

    void setFloat(const GLchar* varName,float f) ;
    void setInt(const GLchar* varName,int f) ;
    void setDouble(const GLchar* varName,double f) ;

    void setVec3(const GLchar* vecName,const glm::vec3 &vec3) ;
    void setVec3(const GLchar* vecName,GLdouble x,GLdouble y,GLdouble z) ;

    void setVec4(const GLchar* vecName,const glm::vec4 &vec4) ;
    void setVec4(const GLchar* vecName,GLdouble x,GLdouble y,GLdouble z,GLdouble w) ;

    void setMat4(const GLchar *matName,const glm::mat4 &mat4) ;
};


#endif // _SHADER_H
