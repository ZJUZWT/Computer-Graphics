#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const GLint W = 756 ;
const GLint H = 756 ;

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location=0) in vec3 aPos;\n"
                                 "void main() {\n"
                                 "gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0) ;\n"
                                 "}\0"
                                 ;
const char* fragmentShaderSource1 = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main() {\n"
                                   "    FragColor = vec4(0.5f,1.0f,1.0f,1.0f) ;\n"
                                   "}\n\0"
;

const char* fragmentShaderSource2 = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main() {\n"
                                   "    FragColor = vec4(1.0f,0.5f,0.2f,1.0f) ;\n"
                                   "}\0"
;

void myInit() ;
void refresh() ;
void framebuffer_size_callback(GLFWwindow* window, int width, int height) ;
void processInput(GLFWwindow *window) ;

int main() {
    myInit() ;

    GLFWwindow* window = glfwCreateWindow(W,H,"Tri",nullptr,nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
//-----------------------------------------------------------------------
    unsigned int vertexShader ;
    vertexShader = glCreateShader(GL_VERTEX_SHADER) ;
    glShaderSource(vertexShader,1,&vertexShaderSource, nullptr) ;
    glCompileShader(vertexShader) ;

    int success ;
    char infoLog[512] ;
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success) ;
    if ( !success ) {
        glGetShaderInfoLog(vertexShader,512, nullptr,infoLog) ;
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
//-----------------------------------------------------------------------
    unsigned int fragmentShader ;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER) ;
    glShaderSource(fragmentShader,1,&fragmentShaderSource1, nullptr) ;
    glCompileShader(fragmentShader) ;

    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success) ;
    if ( !success ) {
        glGetShaderInfoLog(fragmentShader,512, nullptr,infoLog) ;
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

//-----------------------------------------------------------------------
    unsigned int shaderProgram1 ;
    shaderProgram1 = glCreateProgram() ;

    glAttachShader(shaderProgram1,vertexShader) ;
    glAttachShader(shaderProgram1,fragmentShader) ;
    glLinkProgram(shaderProgram1) ;

    glGetProgramiv(shaderProgram1,GL_LINK_STATUS,&success) ;
    if (!success ) {
        glGetProgramInfoLog(shaderProgram1,512, nullptr,infoLog) ;
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl ;
    }
//-----------------------------------------------------------------------
    glDeleteShader(fragmentShader) ;
//-----------------------------------------------------------------------
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER) ;
    glShaderSource(fragmentShader,1,&fragmentShaderSource2, nullptr) ;
    glCompileShader(fragmentShader) ;

    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success) ;
    if ( !success ) {
        glGetShaderInfoLog(fragmentShader,512, nullptr,infoLog) ;
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl ;
    }
//-----------------------------------------------------------------------
    unsigned int shaderProgram2 = glCreateProgram() ;
    glAttachShader(shaderProgram2,vertexShader) ;
    glAttachShader(shaderProgram2,fragmentShader) ;
    glLinkProgram(shaderProgram2) ;

    glGetProgramiv(shaderProgram2,GL_LINK_STATUS,&success) ;
    if ( !success ) {
        glGetShaderInfoLog(shaderProgram2,512, nullptr,infoLog) ;
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl ;
    }
//-----------------------------------------------------------------------
    glDeleteShader(vertexShader) ;
    glDeleteShader(fragmentShader) ;
//-----------------------------------------------------------------------
    float vertices[] = {
             0.5f, 0.5f,0.0f,
             0.5f,-0.5f,0.0f,
            -0.5f,-0.5f,0.0f,
            -0.5f, 0.5f,0.0f,
             0.7f, 0.7f,0.0f
    };
    unsigned int indices[] = {  // note that we start from 0!
            4, 1, 2,  // first Triangle
            2, 3, 4   // second Triangle
    };
//-----------------------------------------------------------------------
    unsigned int VBO , VAO , EBO ;
    glGenVertexArrays(1,&VAO) ;
    glGenBuffers(1,&VBO) ;
    glGenBuffers(1,&EBO) ;

    glBindVertexArray(VAO) ;

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW) ;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW) ;

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0) ;
    glEnableVertexAttribArray(0) ;

    glBindBuffer(GL_ARRAY_BUFFER,0) ;
    glBindVertexArray(0) ;
//-----------------------------------------------------------------------
    while(!glfwWindowShouldClose(window)) {
        processInput(window) ;

        refresh() ;

        glUseProgram(shaderProgram1) ;
        glBindVertexArray(VAO) ;
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT, nullptr) ;
        glUseProgram(shaderProgram2) ;
        glBindVertexArray(VAO) ;
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)(3*sizeof(int))) ;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram1) ;
    glDeleteProgram(shaderProgram2) ;
    glDeleteVertexArrays(1,&VAO) ;
    glDeleteBuffers(1,&VBO) ;
    glDeleteBuffers(1,&EBO) ;

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void refresh() {
    glClearColor(0.5,0.5,0.5,1.0) ;
    glClear(GL_COLOR_BUFFER_BIT) ;
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void myInit() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}