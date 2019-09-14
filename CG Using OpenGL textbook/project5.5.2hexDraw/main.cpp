#include <GL/freeglut.h>
#include <cstdio>
#include <cmath>

const GLint W = 756 ;
const GLint H = 756 ;
const GLdouble pi = 3.1415926 ;
const GLdouble black[3] = {0.0,0.0,0.0};
const GLdouble red[3] = {1.0,0.0,0.0};
const GLdouble blue[3] = {0.0,0.0,1.0};
const GLdouble radii = 18 ;
GLdouble t = 0 , direction = 1 ;

void myDisplay() ;
void myInit() ;
void myIdle() ;
void setWindow(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble near_val,GLdouble far_val)  ;
void setViewport(GLint left,GLint right,GLint bottom,GLint top) ;

void initCT() ;
void popCT() ;
void pushCT() ;
bool checkStackCT() ;
void scale2D(GLdouble sx,GLdouble sy) ;
void translate2D(GLdouble dx,GLdouble dy) ;
void rotate2D(GLdouble theta) ;

void drawLine(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2,GLdouble r,GLdouble g,GLdouble b) ;
void drawDot(GLdouble x,GLdouble y,GLdouble r,GLdouble g,GLdouble b) ;
void drawHex(GLdouble x,GLdouble y,GLdouble radius,GLdouble r,GLdouble g,GLdouble b) ;

int main(int argc,char**argv) {
    glutInit(&argc,argv) ;
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE ) ;
    glutInitWindowPosition(100,100) ;
    glutInitWindowSize(W,H) ;
    glutCreateWindow("circle check") ;

    myInit() ;

    glutDisplayFunc(&myDisplay) ;
    glutIdleFunc(&myIdle) ;

    glutMainLoop() ;
    return 0;
}

const GLdouble sigma = 0.18 ;
const GLdouble sigma2 = sigma*sigma ;
GLdouble normalDis(GLdouble x) {
    return 1/sqrt(2*pi)/sigma*exp( -pow(x-0.5,2) / (2*sigma2) ) ;
}

void myIdle() {
    t += normalDis(t-floor(t))*direction/200 ;
    if ( t > 1 ) direction *= -1 , t = 1-1e-6 ;
    if ( t < 0 ) direction *= -1 , t = 1e-6 ;
    setWindow(0,W,0,H,0,-t*1000) ;
    myDisplay() ;
}

const GLint xNum = 100 ;
const GLint yNum = 100 ;

void myDisplay() {
    GLdouble changeX = radii*3/2 ;
    GLdouble changeY = radii*sqrt(3)/2 ;

    glClear(GL_COLOR_BUFFER_BIT) ;
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity() ;
    translate2D(W/2,H/2) ;
    rotate2D(t*90) ;
    scale2D(t*10,t*10) ;
    translate2D(-W/2,-H/2) ;
    translate2D(-50*radii,-50*radii) ;
    pushCT() ;

    for ( int row = 1 ; row <= yNum ; row++ ) {
        pushCT() ;
        for ( int col = 1 ; col <= xNum ; col++ ) {
            GLdouble r = (GLdouble)row/yNum , g = 0 , b = 0 ;
//            if ( row == 50 && col == 50 ) r = 1.0 ;
            drawHex(0,0, radii, r,g,b);
            if ( col % 2 )
                translate2D(changeX,changeY) ;
            else
                translate2D(changeX,-changeY) ;
        }
        popCT() ;
        translate2D( 0 , 2*changeY ) ;
    }
    popCT() ;
    glutSwapBuffers() ;
}

void drawLine(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2,GLdouble r,GLdouble g,GLdouble b) {
    glColor3f(r,g,b) ;
    glBegin(GL_LINE_STRIP) ;
    glVertex2f(x1,y1) ;
    glVertex2f(x2,y2) ;
    glEnd() ;
}

void drawDot(GLdouble x,GLdouble y,GLdouble r,GLdouble g,GLdouble b) {
    glColor3f(r,g,b) ;
    glBegin(GL_POINTS) ;
    glVertex2f(x,y) ;
    glEnd() ;
}

void drawHex(GLdouble x,GLdouble y,GLdouble radius,GLdouble r,GLdouble g,GLdouble b) {
    glColor3f(r,g,b) ;

    glBegin(GL_LINE_STRIP) ;glMatrixMode(GL_MODELVIEW) ;
    for ( int i = 0 ; i <= 6 ; i++ ) {
        glVertex2f( radius*cos(i*pi/3)+x , radius*sin(i*pi/3)+y ) ;
    }
    glEnd() ;
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
    glClearColor(1.0,1.0,1.0,0.0) ;
    glColor3f(black[0],black[1],black[2]) ;
    glPointSize(5.0) ;
    glLineWidth(1.0) ;
    setWindow(0,W,0,H,0,0) ;
    setViewport(0,W,0,H) ;
    initCT() ;
}

void initCT() {
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity() ;
}

bool checkStackCT() {
    if ( glutGet(GL_MODELVIEW_STACK_DEPTH) <= 1 )
        return false ;
    else
        return true ;
}

void popCT() {
    glMatrixMode(GL_MODELVIEW) ;
    glPopMatrix() ;
}

void pushCT() {
    glMatrixMode(GL_MODELVIEW) ;
    glPushMatrix() ;
}

void scale2D(GLdouble sx,GLdouble sy) {
    glMatrixMode(GL_MODELVIEW) ;
    glScaled(sx,sy,1.0) ;
}

void translate2D(GLdouble dx,GLdouble dy) {
    glMatrixMode(GL_MODELVIEW) ;
    glTranslated(dx,dy,1) ;
}

void rotate2D(GLdouble theta) {
    glMatrixMode(GL_MODELVIEW) ;
    glRotated(theta,0.0,0.0,1.0) ;
}