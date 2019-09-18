//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdio>

#include "init.h"
#include "LoadElement.h"
#include "Shader.h"

const GLint W = 756 ;
const GLint H = 756 ;

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) ;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
void processInput(GLFWwindow *window) ;

void changeSize(GLFWwindow *window,GLint width,GLint height) ;

int main() {
//----------------------------------------------------------------------------------------- Init ↓
    myStartInit() ;
    GLFWwindow *window = glfwCreateWindow(W,H,"translate Test",nullptr,nullptr) ;
    if ( !checkWindows(window) ) { return -1 ; }
    if ( !checkGlad() ) { return -1 ; }

    glfwSetCursorPosCallback(window,mouse_callback) ;
    glfwSetFramebufferSizeCallback(window,changeSize) ;
//----------------------------------------------------------------------------------------- Init ↑ Load Texture ↓
    unsigned int texture1 ;
    if ( createTexture("../container.jpg",GL_TEXTURE_2D,&texture1,GL_RGB,false) == FAIL_LOAD_PIC ) {
        printf( "Failed to load picture ../container.jpg" ) ;
        return -1 ;
    }

    unsigned int texture2 ;
    if ( createTexture("../awesomeface.png",GL_TEXTURE_2D,&texture2,GL_RGBA,true) == FAIL_LOAD_PIC ) {
        printf( "Failed to load picture ../awesomeface.png" ) ;
        return -1 ;
    }
//----------------------------------------------------------------------------------------- Load Texture ↑ Load VAO ↓
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int indices[] = {
            0,1,3,
            2,1,3
    };
    unsigned int VAO,VBO,EBO ;

//    createVAO(&VAO,&VBO,&EBO,sizeof(vertices),vertices,sizeof(indices),indices) ;
    createVAO(&VAO,&VBO,sizeof(vertices),vertices) ;
//----------------------------------------------------------------------------------------- Load VAO ↑ Load Shader ↓
    Shader shader = Shader("../vertexShader.vs","../fragmentShader.fs") ;
    shader.use() ;
    glUniform1i(glGetUniformLocation(shader.id,"texture1"),0) ;
    glUniform1i(glGetUniformLocation(shader.id,"texture2"),1) ;
//----------------------------------------------------------------------------------------- Load Shader ↑ Load Matrix ↓
//    glm::mat4 trans = glm::mat4(1.0f) ;
//    trans = glm::rotate(trans,glm::radians(90.0f),glm::vec3(0.0,0.0,1.0)) ;
//    trans = glm::scale(trans,glm::vec3(0.5,0.5,0.5)) ;
//    glUniformMatrix4fv(glGetUniformLocation(shader.id,"transform"),1,GL_FALSE,glm::value_ptr(trans)) ;
//    glm::mat4 model = glm::mat4(1.0f) ;
//    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    glUniformMatrix4fv(glGetUniformLocation(shader.id,"model"),1,GL_FALSE,glm::value_ptr(model)) ;
//
//    glm::mat4 view = glm::mat4(1.0f) ;
//    view = glm::translate(view,glm::vec3(0.0,0.0,-3.0f)) ;
//    glUniformMatrix4fv(glGetUniformLocation(shader.id,"view"),1,GL_FALSE,glm::value_ptr(view)) ;
//
//    glm::mat4 projection = glm::mat4(1.0f) ;
//    projection = glm::perspective(glm::radians(60.0f),(float)W/H,0.1f,100.0f) ;
//    glUniformMatrix4fv(glGetUniformLocation(shader.id,"projection"),1,GL_FALSE,glm::value_ptr(projection)) ;
    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glEnable(GL_DEPTH_TEST) ;
//----------------------------------------------------------------------------------------- Load Matrix ↑ Load Loop ↓
    while ( !glfwWindowShouldClose(window) ) {
        myLoopInit() ;

        processInput(window) ;

        glActiveTexture(GL_TEXTURE0) ;
        glBindTexture(GL_TEXTURE_2D,texture1) ;
        glActiveTexture(GL_TEXTURE1) ;
        glBindTexture(GL_TEXTURE_2D,texture2) ;

        shader.use() ;
//        glm::mat4 trans = glm::mat4(1.0f) ;
//        trans = glm::rotate(trans,(float)glfwGetTime(),glm::vec3(0.0,0.0,1.0)) ;
//        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
//        trans = glm::scale(trans,glm::vec3(0.5,0.5,0.5)) ;
//        glUniformMatrix4fv(glGetUniformLocation(shader.id,"transform"),1,GL_FALSE,glm::value_ptr(trans)) ;
        float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;

        glBindVertexArray(VAO) ;
        for ( int i = 0 ; i < 10 ; i++ ) {
            glm::mat4 model = glm::mat4(1.0f) ;
            glm::mat4 view = glm::mat4(1.0f) ;
            glm::mat4 projection = glm::mat4(1.0f) ;

            model = glm::translate(model,cubePositions[i]) ;
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(glGetUniformLocation(shader.id,"model"),1,GL_FALSE,glm::value_ptr(model)) ;

//            view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
//            view = glm::translate(view,glm::vec3(0.0,0.0,-5.0f));
            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            glUniformMatrix4fv(glGetUniformLocation(shader.id,"view"),1,GL_FALSE,glm::value_ptr(view)) ;

            projection = glm::perspective(glm::radians(45.0f),(float)W/H,0.01f,100.0f) ;
            glUniformMatrix4fv(glGetUniformLocation(shader.id,"projection"),1,GL_FALSE,glm::value_ptr(projection)) ;

            glDrawArrays(GL_TRIANGLES,0,36) ;
        }
//        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr) ;
        glfwSwapBuffers(window) ;
        glfwPollEvents() ;
    }
//----------------------------------------------------------------------------------------- Load Loop ↑

    glfwTerminate() ;
    return 0 ;
}

void changeSize(GLFWwindow *window,GLint width,GLint height) {
    glViewport(0,0,width,height) ;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 1;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f) pitch = 89.0f;
    if(pitch < -89.0f) pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void processInput(GLFWwindow *window) {
    float cameraSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}