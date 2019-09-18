#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
#include "Shader.h"

const GLint W = 756 ;
const GLint H = 756 ;

const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location=0) in vec3 aPos;\n"
        "out vec4 vertexColor;\n"
        "void main() {\n"
        "   gl_Position = vec4(aPos,1.0f) ;\n"
        "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
        "}\0";

const char* fragmentShaderSource =
        "#version 330 core\n"
        "in vec4 vertexColor;\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "   fragColor = vertexColor;\n"
        "}\0" ;

const char* fragmentShaderSource2 =
        "#version 330 core\n"
        "uniform vec4 uniColor;\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "   fragColor = uniColor;\n"
        "}\0" ;

void myInit() ;
bool checkGlad() ;
bool checkWindows(GLFWwindow* window) ;

void framebuffer_size_callback(GLFWwindow *window,GLint width,GLint height) ;

bool shaderProgramCreate(unsigned int *vShader,unsigned int *fShader,unsigned int *sProgram,const char* vSource,const char* fSource) ;
void shaderCreate(unsigned int *shader,const char* source,int shaderType) ;
bool checkShaderCompile(unsigned const int *shader) ;
bool checkProgramLink(unsigned const int *program) ;

void bindVAO(unsigned int *VAO,unsigned int *VBO,unsigned int *EBO,unsigned int sizeVertices,float *vertices,unsigned int sizeIndices,unsigned int *indices) ;



int main() {
    myInit() ;
    GLFWwindow *window = glfwCreateWindow(W,H,"shaderTest", nullptr, nullptr) ;
    if (!checkWindows(window)) return -1 ;
    if (!checkGlad()) return -1 ;

//-----------------------------------------------------------------------------------
    unsigned int vertexShader ;
    unsigned int fragmentShader ;
    unsigned int shaderProgram ;
    shaderProgramCreate(&vertexShader,&fragmentShader,&shaderProgram,vertexShaderSource,fragmentShaderSource) ;
    unsigned int vertexShader2 ;
    unsigned int fragmentShader2 ;
    unsigned int shaderProgram2 ;
    shaderProgramCreate(&vertexShader2,&fragmentShader2,&shaderProgram2,vertexShaderSource,fragmentShaderSource2) ;

    Shader shader = Shader(
            "../vertexShader.vs",
            "../fragmentShader.fs") ;
//-----------------------------------------------------------------------------------
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
             0.0f, -0.5f, 0.0f
    };
    unsigned int indices1[] = {
            0 , 2 , 3
    };
    unsigned int indices2[] = {
            1 , 2 , 3
    };
    unsigned int VAO1 , VBO1 , EBO1 ;
    bindVAO(&VAO1,&VBO1,&EBO1,sizeof(vertices),vertices,sizeof(indices1),indices1) ;
    unsigned int VAO2 , EBO2 ;
    bindVAO(&VAO2,&VBO1,&EBO2,sizeof(vertices),vertices,sizeof(indices2),indices2) ;
//-----------------------------------------------------------------------------------
    float vertex[] = {
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };
    unsigned int VAO3 , VBO3 ;

    glGenVertexArrays(1,&VAO3) ;
    glGenBuffers(1,&VBO3) ;

    glBindVertexArray(VAO3) ;
    glBindBuffer(GL_ARRAY_BUFFER,VBO3) ;
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW) ;

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),nullptr) ;
    glEnableVertexAttribArray(0) ;
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float))) ;
    glEnableVertexAttribArray(1) ;

    glBindBuffer(GL_ARRAY_BUFFER,0) ;
    glBindVertexArray(0) ;
//-----------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window)) {

//        float time = glfwGetTime() ;
//        float greenValue = (sin(time)/2.0f)+0.5f ;

        glClearColor(0.5f,0.5f,0.5f,1.0f) ;
        glClear(GL_COLOR_BUFFER_BIT) ;

        shader.use() ;
        glBindVertexArray(VAO3) ;
        glDrawArrays(GL_TRIANGLES,0,3) ;
//        glUseProgram(shaderProgram) ;
//        glBindVertexArray(VAO1) ;
//        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,nullptr) ;
//
//        glUseProgram(shaderProgram2) ;
//        glUniform4f(glGetUniformLocation(shaderProgram2,"uniColor"),1.0f,greenValue,0.2f,1.0f) ;
//        glBindVertexArray(VAO2) ;
//        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,nullptr) ;

        glfwSwapBuffers(window) ;
        glfwPollEvents() ;
    }

    glDeleteBuffers(1,&VBO1) ;
    glDeleteBuffers(1,&EBO1) ;
    glDeleteVertexArrays(1,&VAO1) ;
    glDeleteProgram(shaderProgram) ;
    glfwTerminate() ;
    return 0 ;
}

void bindVAO(unsigned int *VAO,unsigned int *VBO,unsigned int *EBO,unsigned int sizeVertices,float *vertices,unsigned int sizeIndices,unsigned int *indices) {
    glGenVertexArrays(1,VAO) ;
    glBindVertexArray(*VAO) ;

    glGenBuffers(1,VBO) ;
    glBindBuffer(GL_ARRAY_BUFFER,*VBO) ;
    glBufferData(GL_ARRAY_BUFFER,sizeVertices,vertices,GL_STATIC_DRAW) ;

    glGenBuffers(1,EBO) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,*EBO) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeIndices,indices,GL_STATIC_DRAW) ;

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float), nullptr) ;
    glEnableVertexAttribArray(0) ;

    glBindBuffer(GL_ARRAY_BUFFER,0) ;
    glBindVertexArray(0) ;
}

bool shaderProgramCreate(unsigned int *vShader,unsigned int *fShader,unsigned int *sProgram,const char* vSource,const char* fSource) {
    shaderCreate(vShader,vSource,GL_VERTEX_SHADER) ;
    if ( !checkShaderCompile(vShader) ) return false ;
    shaderCreate(fShader,fSource,GL_FRAGMENT_SHADER) ;
    if ( !checkShaderCompile(fShader) ) return false ;

    *sProgram = glCreateProgram() ;
    glAttachShader(*sProgram,*vShader) ;
    glAttachShader(*sProgram,*fShader) ;
    glLinkProgram(*sProgram) ;
    return checkProgramLink(sProgram) ;
}

void shaderCreate(unsigned int *shader,const char* source,int shaderType) {
    *shader = glCreateShader(shaderType) ;
    glShaderSource(*shader,1,&source, nullptr) ;
    glCompileShader(*shader) ;
}

bool checkProgramLink(unsigned const int *program) {
    int success ; char infoLog[512] ;
    glGetProgramiv(*program,GL_LINK_STATUS,&success) ;
    if ( !success ) {
        glGetShaderInfoLog(*program,512, nullptr,infoLog) ;
        std::cout << "failed to link :" << infoLog << std::endl ;
        return false ;
    }
    return true ;
}

bool checkShaderCompile(unsigned const int *shader) {
    int success ; char infoLog[512] ;
    glGetShaderiv(*shader,GL_COMPILE_STATUS,&success) ;
    if ( !success ) {
        glGetShaderInfoLog(*shader,512, nullptr,infoLog) ;
        std::cout << "failed to compile :" << infoLog << std::endl ;
        return false ;
    }
    return true ;
}

void myInit() {
    glfwInit() ;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3) ;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3) ;
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE) ;
}

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
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback) ;
    return true ;
}

void framebuffer_size_callback(GLFWwindow *window,GLint width,GLint height) {
    glViewport(0,0,width,height) ;
}