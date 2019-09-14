#include <GL/glut.h>
#include <cstdio>
#include <cmath>

const GLint W = 720 ;
const GLint H = 720 ;
const GLint numHex = 100 ;
const GLdouble angleHex = 85 ;
const GLdouble length = 0.1 ;
const GLdouble pi = 3.1415926 ;

GLdouble direction = 1 ;
GLdouble minusSize = 0 ;

void myDisplay() ;
void myIdle() ;
void myInit() ;
void setWindow(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top) ;
void setViewport(GLint left,GLint right,GLint bottom,GLint top) ;
void hexSwirl(GLint left,GLint right,GLint bottom,GLint top,GLint num,GLdouble angle);

GLdouble t = 0 ;
const GLdouble numRose = 6 ;
const GLdouble radius = 20 ;
const GLdouble zoomSize = 1.2 ;
void roseCurve(GLdouble left,GLdouble right);

int main(int argc,char**argv) {
    glutInit(&argc,argv) ;
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE ) ;
    glutInitWindowSize(W,H) ;
    glutInitWindowPosition(100,100) ;
    glutCreateWindow("Hex") ;

    glutDisplayFunc(&myDisplay) ;
    glutIdleFunc(&myIdle) ;

    myInit() ;

    glutMainLoop() ;
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT) ;

//    setWindow(-length*numHex+minusSize,+length*numHex-minusSize,-length*numHex+minusSize,+length*numHex-minusSize) ;
//    for ( int i = 0 ; i < 3 ; i++ )
//        for ( int j = 0 ; j < 3 ; j++ )
//            hexSwirl(i*W/3,j*H/3,W/3,H/3,numHex,angleHex) ;

    setWindow(-radius*zoomSize,radius*zoomSize,-radius*zoomSize,radius*zoomSize) ;
    roseCurve( 0 , t ) ;

    glFlush() ;
    glutSwapBuffers() ;
    minusSize += 0.1*direction ;
    if ( fabs(minusSize-length*numHex) > 10 ) direction *= -1 ;
}

void myIdle() {
    t += 0.002 ;

    myDisplay() ;
}

void myInit() {
    glClearColor( 1.0 , 1.0 , 1.0 , 0.0 ) ;
    glColor3f( 0.0 , 0.0 , 0.0 ) ;
    glLineWidth( 1.0 ) ;
}

void setWindow(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top) {
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    gluOrtho2D( left , right , bottom , top ) ;
}

void setViewport(GLint left,GLint right,GLint bottom,GLint top) {
    glViewport( left , bottom , right-left , top-bottom ) ;
}

void hexSwirl(GLint left,GLint right,GLint width,GLint height,GLint num,GLdouble angle) {
    GLdouble offset = 0 ;
    GLdouble offsetPerNum = angle/num/180*pi ;
//    setViewport(left,right,bottom,top) ;
    glViewport(left,right,width,height) ;
    for ( int i = num ; i >= 1 ; i-- ) {
        glBegin(GL_LINE_STRIP) ;
        for ( int j = 0 ; j <= 6 ; j++ ) {
            glVertex2d( i*length*cos((j%6)*pi/3+offset) , i*length*sin((j%6)*pi/3+offset) ) ;
        }
        glEnd() ;
        offset += offsetPerNum ;
    }
}

GLdouble f(GLdouble x) {
    return radius*sin(numRose*x) ;
}

void roseCurve(GLdouble left,GLdouble right) {
    glBegin(GL_LINE_STRIP) ;
    for ( GLdouble theta = left ; theta <= right ; theta+=0.001 ) {
        glVertex2f( f(theta+t)*cos(theta) , f(theta+t)*sin(theta) ) ;
    }
    glEnd() ;
}
