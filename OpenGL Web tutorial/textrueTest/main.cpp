#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "init.h"
#include "Shader.h"

const int W = 756 ;
const int H = 756 ;

void framebuffer_size_callback(GLFWwindow *window,int width,int height) ;

int main() {
    myStartInit() ;
    GLFWwindow *window = glfwCreateWindow(W,H,"texture", nullptr, nullptr) ;
    if (!checkWindows(window)) return -1 ;
    if (!checkGlad()) return -1 ;

    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback) ;
//---------------------------------------------------------------------------------------------
    int w,h,numChannels ;
    unsigned char *picture = stbi_load("../container.jpg",&w,&h,&numChannels,0) ;

    if ( picture == nullptr ) {
        std::cout << "Failed to load image!" << std::endl ;
        return -1 ;
    }
//---------------------------------------------------------------------------------------------
    unsigned int texture1 ;
    glGenTextures(1,&texture1) ;
    glBindTexture(GL_TEXTURE_2D,texture1) ;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,picture) ;
    glGenerateMipmap(GL_TEXTURE_2D) ;

    stbi_image_free(picture) ;
//---------------------------------------------------------------------------------------------
    int w2,h2,numChannels2 ;
    unsigned char *picture2 = stbi_load("../awesomeface.png",&w2,&h2,&numChannels2,0) ;

    if ( picture2 == nullptr ) {
        std::cout << "Failed to load image!" << std::endl ;
        return -1 ;
    }
//---------------------------------------------------------------------------------------------
    unsigned int texture2 ;
    glGenTextures(1,&texture2) ;
    glBindTexture(GL_TEXTURE_2D,texture2) ;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w2,h2,0,GL_RGBA,GL_UNSIGNED_BYTE,picture2) ;
    glGenerateMipmap(GL_TEXTURE_2D) ;

    stbi_image_free(picture2) ;
//---------------------------------------------------------------------------------------------
    float vertices[] = {
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };
    unsigned int indices[] = {
            0,1,3,
            2,1,3
    };

    unsigned int VAO,VBO,EBO;
    glGenVertexArrays(1,&VAO) ;
    glGenBuffers(1,&VBO) ;
    glGenBuffers(1,&EBO) ;

    glBindVertexArray(VAO) ;
    glBindBuffer(GL_ARRAY_BUFFER,VBO) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO) ;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW) ;

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),nullptr) ;
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(sizeof(float)*3)) ;
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(sizeof(float)*6)) ;

    glEnableVertexAttribArray(0) ;
    glEnableVertexAttribArray(1) ;
    glEnableVertexAttribArray(2) ;

    glBindBuffer(GL_ARRAY_BUFFER,0) ;
    glBindVertexArray(0) ;

//    printf( "check point : 6 \n" ) ;

//---------------------------------------------------------------------------------------------
    Shader shader = Shader("../vertexShader.vs","../fragmentShader.fs") ;
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
    shader.use() ;
    glUniform1i(glGetUniformLocation(shader.id,"texture1"),0) ;
    glUniform1i(glGetUniformLocation(shader.id,"texture2"),1) ;

//---------------------------------------------------------------------------------------------
    while ( !glfwWindowShouldClose(window) ) {
        myLoopInit() ;

        glActiveTexture(GL_TEXTURE0) ;
        glBindTexture(GL_TEXTURE_2D,texture1) ;
        glActiveTexture(GL_TEXTURE1) ;
        glBindTexture(GL_TEXTURE_2D,texture2) ;

        shader.use() ;
        glBindVertexArray(VAO) ;
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr) ;

        glfwSwapBuffers(window) ;
        glfwPollEvents() ;
    }
    return 0 ;
}

void framebuffer_size_callback(GLFWwindow *window,int width,int height) {
    glViewport(0,0,width,height) ;
}