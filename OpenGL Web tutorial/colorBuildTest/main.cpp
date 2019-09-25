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

const int W = 1920 ;
const int H = 1080 ;

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) ;

glm::vec3 cameraPos   = glm::vec3(1.0f, 1.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

glm::vec3 colorLight = glm::vec3(1.0f) ;
glm::vec3 colorObject = glm::vec3(1.0f,0.5f,0.31f) ;

void processInput(GLFWwindow *window) ;
void changeSize(GLFWwindow *window,GLint width,GLint height) ;

int main() {
//----------------------------------------------------------------------------------------- Init ↓
    myStartInit() ;
    GLFWwindow *window = glfwCreateWindow(W,H,"light color Test",glfwGetPrimaryMonitor(),nullptr) ;
    if ( !checkWindows(window) ) { return -1 ; }
    if ( !checkGlad() ) { return -1 ; }

    glfwSetCursorPosCallback(window,mouse_callback) ;
    glfwSetFramebufferSizeCallback(window,changeSize) ;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//----------------------------------------------------------------------------------------- Init ↑ Load Texture ↓
    unsigned int texture ;
    if ( createTexture("../container2.png",GL_TEXTURE_2D,&texture,GL_RGBA,GL_FALSE) == FAIL_LOAD_PIC ) {
        std::cout << "failed to load container2" << std::endl ;
        return -1 ;
    }
    unsigned int specularTexture ;
    if ( createTexture("../container2_specular.png",GL_TEXTURE_2D,&specularTexture,GL_RGBA,GL_FALSE) == FAIL_LOAD_PIC ) {
        std::cout << "failed to load container2_specular" << std::endl ;
        return -1 ;
    }
//----------------------------------------------------------------------------------------- Load Texture ↑ Load VAO ↓
    float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    unsigned int VAO,VBO,lightVAO;

    createVAOVNT(&VAO,&VBO,sizeof(vertices),vertices,8*sizeof(float)) ;
    createVAOV(&lightVAO,&VBO,sizeof(vertices),vertices,8*sizeof(float)) ;
//----------------------------------------------------------------------------------------- Load VAO ↑ Load Shader ↓
    Shader objShader = Shader("../vertexShader.vs","../fragmentShader.fs") ;
    Shader lightShader = Shader("../lightShader.vs","../lightShader.fs") ;
//----------------------------------------------------------------------------------------- Load Shader ↑ Load Texture ↓
    glEnable(GL_DEPTH_TEST) ;
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::vec3 lightPosNow = lightPos ;

    objShader.use() ;
    objShader.setInt("material.diffuse",0) ;
    objShader.setInt("material.specular",1) ;

//----------------------------------------------------------------------------------------- Load Texture ↑ Load Loop ↓
    while ( !glfwWindowShouldClose(window) ) {
        myLoopInit() ;

        processInput(window) ;


//ObjectShader

        //position
        objShader.use() ;

        glm::mat4 rotateMatrix(1.0f) ;
        rotateMatrix = glm::rotate(rotateMatrix,(float)glfwGetTime(),glm::vec3(0.0f,0.0f,0.1f) ) ;
        lightPosNow = glm::vec3(glm::vec4(lightPos,1.0f)*rotateMatrix) ;

        objShader.setVec3("light.position", lightPosNow ) ;
        objShader.setVec3("viewPos", cameraPos) ;

        //light attribute
        objShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        objShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        objShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        //material attribute
        objShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        objShader.setFloat("material.shininess", 64.0f);

        //Matrix
        glm::mat4 model = glm::mat4(1.0f) ;
        glm::mat4 view = glm::mat4(1.0f) ;
        glm::mat4 projection = glm::mat4(1.0f) ;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        projection = glm::perspective(glm::radians(45.0f),(float)W/H,0.01f,100.0f) ;

        objShader.setMat4("model",model) ;
        objShader.setMat4("view",view) ;
        objShader.setMat4("projection",projection) ;

        glBindVertexArray(VAO) ;

        glActiveTexture(GL_TEXTURE0) ;
        glBindTexture(GL_TEXTURE_2D,texture) ;
        glActiveTexture(GL_TEXTURE1) ;
        glBindTexture(GL_TEXTURE_2D,specularTexture) ;

        glDrawArrays(GL_TRIANGLES,0,36) ;

//lightShader

        //Matrix
        lightShader.use() ;
        lightShader.setVec3("colorLight",colorLight) ;
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosNow);
        model = glm::scale(model, glm::vec3(0.2f));

        lightShader.setMat4("model",model) ;
        lightShader.setMat4("view",view) ;
        lightShader.setMat4("projection",projection) ;
        glBindVertexArray(lightVAO) ;
        glDrawArrays(GL_TRIANGLES,0,36) ;

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

    float sensitivity = 0.3;
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
    float cameraSpeed = 0.1f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}