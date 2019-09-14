#include <GL/glut.h>
#include <cmath>
#include <cstdio>

const GLint W = 512 ;
const GLint H = 512 ;
const GLdouble pi = 3.1415926 ;
const GLdouble windowSizePattern[4] {-2.5,2.5,-2.5,2.5};
const GLdouble windowSizeChars[4] {-1,5,-1,5};

void drawTweenChars() ;
void updateTweenChars() ;
const GLdouble chars[3][14][2] = {
        0.0,4.0 , 4.0,4.0 , 4.0,3.5 , 2.92,2.51 , 1.67,1.34 , 0.75,0.5 , 4.0,0.5 , 4,0.0 , 0.0,0.0 , 0.0,0.5 , 1.64,2 , 2.18,2.5 , 3.26,3.49 , 0.0,3.5 ,
        0.0,4.0 , 0.3,4.0 , 0.69,0.5 , 1.85,3.59 , 2.14,3.59 , 3.3,0.5 , 3.69,4.0 , 4.0,4.0 , 3.5,0.0 , 3.19,0.0 , 2.1,3.0 , 1.9,3.0 , 0.8,0.0 , 0.5,0.0 ,
        0.0,4.0 , 0.64,4.0 , 1.13,4.0 , 1.64,4.0 , 2.35,4.0 , 2.92,4.0 , 3.5,4.0 , 4.0,4.0 , 4.0,3.37 , 2.29,3.37 , 2.30,0.0 , 1.72,0.0 , 1.72,3.37 , 0.0,3.37
} ;

const GLint numPointsPattern = 512 ;
const GLint numPattern = 6 ;
const GLdouble radius = 2.0 ;
void drawTweenPattern() ;
void updateTweenPattern() ;

GLdouble t = 0 ;
GLdouble direction = 1 ;
GLdouble lerp(GLdouble x1,GLdouble x2) ;
GLdouble normalDis(GLdouble x) ;
GLdouble roseCurveX(GLdouble x) ;
GLdouble roseCurveY(GLdouble x) ;
GLdouble circleX(GLdouble x) ;
GLdouble circleY(GLdouble x) ;

void myDisplay() ;
void myInit() ;
void myIdle() ;
void setWindow(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top) ;
void setViewport(GLint left,GLint right,GLint bottom,GLint top) ;

int main(int argc,char**argv) {
    glutInit(&argc,argv) ;
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE ) ;
    glutInitWindowPosition(100,100) ;
    glutInitWindowSize(W,H) ;
    glutCreateWindow("lerp test") ;

    glutDisplayFunc(&myDisplay) ;
    glutIdleFunc(&myIdle) ;
    myInit() ;
    setViewport(0,W,0,H) ;

    glutMainLoop() ;
}

GLdouble lerp(GLdouble x1,GLdouble x2) {
    return (ceil(t)-t)*x1+(t-floor(t))*x2 ;
}

void drawTweenChars() {
    setWindow(windowSizeChars[0],windowSizeChars[1],windowSizeChars[2],windowSizeChars[3]) ;
    glBegin(GL_LINE_STRIP) ;
    for ( int num = 0 ; num <= 14 ; num++ ) {
        int p = num % 14 , nt = floor(t) ;
        glVertex2f(
                lerp( chars[nt][p][0] , chars[nt+1][p][0] ) ,
                lerp( chars[nt][p][1] , chars[nt+1][p][1] ) ) ;

    }
    glEnd() ;
}

#define CHANGE_X x *= 2*pi/numPointsPattern+t ;
//x *= t ;

GLdouble roseCurveX(GLdouble x) {
    CHANGE_X
    return radius*cos(numPattern*x)*cos(x) ;
}

GLdouble roseCurveY(GLdouble x) {
    CHANGE_X
    return radius*cos(numPattern*x)*sin(x) ;
}

GLdouble circleX(GLdouble x) {
    CHANGE_X
    return radius*cos(x) ;
}

GLdouble circleY(GLdouble x) {
    CHANGE_X
    return radius*sin(x) ;
}

void drawTweenPattern() {
    setWindow(windowSizePattern[0],windowSizePattern[1],windowSizePattern[2],windowSizePattern[3]) ;
    glBegin(GL_LINE_STRIP) ;
    for ( int num = 0 ; num <= numPointsPattern ; num++ ) {
        int p = num % numPointsPattern ;
        glVertex2f(
                lerp( circleX(p) , roseCurveX(p) ) ,
                lerp( circleY(p) , roseCurveY(p) ) );

//        if ( num == numPointsPattern / 4 )
//            printf( "%.1lf %.1lf %.1lf %.1lf %.1lf %.1lf\n" ,
//                    circleX(p) ,
//                    roseCurveX(p) ,
//                    lerp( circleX(p) , roseCurveX(p) ) ,
//                    circleY(p) ,
//                    roseCurveY(p) ,
//                    lerp( circleY(p) , roseCurveY(p) ) ) ;
    }
    glEnd() ;
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT) ;

    glBegin(GL_POINTS) ;
    glVertex2f(0,0) ;
    glEnd() ;

//    drawTweenChars() ;
    drawTweenPattern() ;

    glutSwapBuffers() ;
}

const GLdouble sigma = 0.18 ;
const GLdouble sigma2 = sigma*sigma ;
GLdouble normalDis(GLdouble x) {
    return 1/sqrt(2*pi)/sigma*exp( -pow(x-0.5,2) / (2*sigma2) ) ;
}

void updateTweenChars() {
    t += normalDis(t-floor(t))/100 ;
    if ( t >= 3 ) t -= 3 ;
}

void updateTweenPattern() {
    t += normalDis(t-floor(t))*direction/200 ;
    if ( t > 1 ) direction *= -1 , t = 1-1e-6 ;
    if ( t < 0 ) direction *= -1 , t = 1e-6 ;
}

void myIdle() {
//    updateTweenChars() ;
    updateTweenPattern() ;
    myDisplay() ;
}

void myInit() {
    glClearColor(1.0,1.0,1.0,0.0) ;
    glColor3f(0.0,0.0,0.0) ;
    glLineWidth(2.0) ;
}

void setWindow(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top) {
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    gluOrtho2D(left,right,bottom,top) ;
}

void setViewport(GLint left,GLint right,GLint bottom,GLint top) {
    glViewport( left , bottom , right-left , top-bottom ) ;
}