#include <GLFW/glfw3.h>
#include <GL/gl3w.h>
#include <GL/glcorearb.h>

const GLint W = 756 ;
const GLint H = 756 ;

int main(int argc,char** argv) {
    glfwInit() ;

    GLFWwindow* window = glfwCreateWindow( W,H,"Test",NULL,NULL) ;

    glfwMakeContextCurrent(window) ;
    gl3wInit() ;



}