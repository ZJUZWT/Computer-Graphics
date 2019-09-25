//
// Created by MrKill on 2019/9/13.
//
#include "Shader.h"

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

void Shader::setFloat(const GLchar *varName,float f) {
    glUniform1f(glGetUniformLocation(id,varName),f) ;
}

void Shader::setInt(const GLchar *varName,int f) {
    glUniform1i(glGetUniformLocation(id,varName),f) ;
}

void Shader::setDouble(const GLchar *varName,double f) {
    glUniform1d(glGetUniformLocation(id,varName),f) ;
}


void Shader::setVec3(const GLchar *vecName, GLdouble x, GLdouble y, GLdouble z) {
    glUniform3f(glGetUniformLocation(id,vecName),x,y,z) ;
}
void Shader::setVec3(const GLchar *vecName,const glm::vec3 &vec3) {
    glUniform3fv(glGetUniformLocation(id,vecName),1,&vec3[0]) ;
}

void Shader::setVec4(const GLchar *vecName, const glm::vec4 &vec4) {
    glUniform4fv(glGetUniformLocation(id,vecName),1,&vec4[0]) ;
}
void Shader::setVec4(const GLchar *vecName, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glUniform4f(glGetUniformLocation(id,vecName),x,y,z,w) ;
}

void Shader::setMat4(const GLchar *matName,const glm::mat4 &mat4) {
    glUniformMatrix4fv(glGetUniformLocation(id,matName),1,GL_FALSE,&mat4[0][0]) ;
}