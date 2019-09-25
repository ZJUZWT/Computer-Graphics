#include <GL/freeglut.h>
#include <cstdio>
#include <cmath>
#include <ctime>
#include "SDL.h"

const GLint W = 756 ;
const GLint H = 756 ;
const GLdouble pi = 3.1415926 ;
const GLdouble black[3] = {0.0,0.0,0.0};
const GLdouble red[3] = {1.0,0.0,0.0};
const GLdouble blue[3] = {0.0,0.0,1.0};
const GLdouble radii = 18 ;
GLdouble x = 0 , t = 0 , direction = 1 ;

static Mesh model = Mesh("../dome1.3vn",1) ;
static Mesh function = Mesh("../function.3vn",2) ;

void myDisplay() ;
void myIdle() ;
void myInit() ;
void setWindow(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble near_val,GLdouble far_val)  ;
void setViewport(GLint left,GLint right,GLint bottom,GLint top) ;
void drawXYZ() ;
void drawLine(GLdouble x1,GLdouble y1,GLdouble z1,GLdouble x2,GLdouble y2,GLdouble z2) ;

void initCT() ;
void initLight() ;

int main(int argc,char**argv) {
    glutInit(&argc,argv) ;
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ) ;
    glutInitWindowPosition(100,100) ;
    glutInitWindowSize(W,H) ;
    glutCreateWindow("circle check") ;

    myInit() ;

    glutDisplayFunc(&myDisplay) ;
//    glutIdleFunc(&myIdle) ;
    glutMainLoop() ;
    return 0;
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT) ;
    glPushMatrix() ;

    gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0) ;
//    gluLookAt(0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,-1.0) ;
    drawXYZ() ;

    glColor3f(black[0],black[1],black[2]) ;
    glPointSize(5.0) ;
    glLineWidth(1.0) ;
    function.draw(GL_LINE_LOOP,2) ;
//    glLineWidth(3.0) ;
//    function.draw(GL_LINE_LOOP,2) ;
    glutSwapBuffers() ;
    glPopMatrix() ;
}
void drawLine(GLdouble x1,GLdouble y1,GLdouble z1,GLdouble x2,GLdouble y2,GLdouble z2) {
    glBegin(GL_LINES) ;
    glVertex3f(x1,y1,z1) ;
    glVertex3f(x2,y2,z2) ;
    glEnd() ;
}

void drawXYZ() {
    glLineWidth(3.0) ;
    glColor3f(1.0,0.0,0.0) ;
    drawLine(1000,0,0,-1000,0,0) ;
    glColor3f(0.0,1.0,0.0) ;
    drawLine(0,1000,0,0,-1000,0) ;
    glColor3f(0.0,0.0,1.0) ;
    drawLine(0,0,1000,0,0,-1000) ;
}

void myIdle() {
    static GLint t = clock() ;
    static GLint x = clock() ;
    t = clock() ;
    if ( ( t-x ) > CLOCKS_PER_SEC/60 ) {
        glPopMatrix() ;
        glPushMatrix() ;
        static int num = 0 ;
        num++ ;
//        gluLookAt(sin(num*pi/600),cos(num*pi/600),0.0,0.0,0.0,0.0,0.0,1.0,0.0) ;
//        x = t ;
    }
    myDisplay() ;
}

void setWindow(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble near_val,GLdouble far_val) {
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    glOrtho(left,right,bottom,top,near_val,far_val) ;
}

void setViewport(GLint left,GLint right,GLint bottom,GLint top) {
    glViewport(left,bottom,right-left,top-bottom) ;
}

void myInit() {
//    initLight() ;
    glClearColor(1.0,1.0,1.0,1.0) ;
    setWindow(-100,100,-100,100,-100,100) ;
    setViewport(0,W,0,H) ;
    initCT() ;

    glTranslated(0.0,0.0,0.0) ;
    glScaled(1,1,1) ;
//    gluLookAt(0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0) ;

//    glPushMatrix() ;
//    glPushMatrix() ;
}

void initCT() {
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity() ;
}

void popCT() {
    glMatrixMode(GL_MODELVIEW) ;
    glPopMatrix() ;
}

void pushCT() {
    glMatrixMode(GL_MODELVIEW) ;
    glPushMatrix() ;
}

void initLight() {
    GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f}; // gray
    GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {80.0f};
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    // set the light source properties
    GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat light_position[] = {0.0f, 1.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    glEnable(GL_LIGHTING); // enable the light source
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST); // for hidden surface removal
    glEnable(GL_NORMALIZE); // normalize vectors for proper shading
}