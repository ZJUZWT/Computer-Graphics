#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <cmath>

const GLint W = 512 ;
const GLint H = 512 ;
const GLint MaxRand = 32767 ;
const GLint MaxN = 65536 ;
GLint N = 65536 ;

const int SHOW_NUM_100 = 1 ;
const int SHOW_NUM_1000 = 2 ;
const int SHOW_NUM_10000 = 3 ;
const int SHOW_NUM_100000 = 4 ;

GLdouble A,B,C,D ;
GLint randNum[MaxN+1] ;

void test0() {
    for ( int i = 0 ; i < N ; i++ ) {
        glVertex2f( A*rand()+B , C*rand()+D ) ;
    }
}

void test1() {
    for ( int i = 0 ; i <= N ; i++ )
        randNum[i] = rand() ;
    for ( int i = 0 ; i < N ; i++ )
        glVertex2f( A*randNum[i]+B , C*randNum[i+1]+D ) ;
}

GLint randSeed[2] = { 857242 , 785742 };
GLint lastNum ;

GLint getRandNum() {
    lastNum = lastNum*randSeed[0] + randSeed[1] ;
    lastNum %= MaxRand ;
    return lastNum ;
}

void test2() {
    lastNum = rand() ;
    for ( int i = 0 ; i < N ; i++ ) {
        glVertex2f( A*getRandNum()+B , C*getRandNum()+D ) ;
    }
}

void test3() {
    for ( int i = 0 ; i < N ; i++ ) {
        glVertex2f( (GLdouble)W*i/N+B , C*getRandNum()+D ) ;
    }
}

void myInit() {
    glClearColor(1.0,1.0,1.0,0);
    glColor3f(0.0,0.0,0.0) ;
    glPointSize(2.0f) ;

    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    gluOrtho2D( 0.0, (GLdouble) W , 0.0 , (GLdouble) H ) ;

    A = (GLdouble)W/MaxRand; B = 0 ;
    C = (GLdouble)H/MaxRand; D = 0 ;
}

GLint downList(GLint num) {
    GLint sum = 0 ;
    while( num != 1 ) {
        if ( num%2 ) num = num*3+1 ; else num /= 2 ;
        sum++ ;
    }
    return sum ;
}

void reCalcCoefficient() {
    GLint downMax = -0xFFFFFFFF , downMin = 0xFFFFFFFF ;
    for ( GLint i = 0 ; i < N ; i++ ) {
        GLint downNum = downList(i+1) ;
        downMax = fmax( downMax , downNum ) ;
        downMin = fmin( downMin , downNum ) ;
    }
    C = (GLdouble)H/(downMax-downMin+5) ; D = 1 ;
}

void test4() {
    reCalcCoefficient() ;
    glEnd() ;
    glBegin(GL_POINTS) ;
    for ( GLint i = 0 ; i < N ; i++ ) {
        glVertex2d( (GLdouble)W*i/N+B , C*downList(i+1)+D ) ;
    }
    glFlush() ;
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT) ;
    glBegin(GL_POINTS) ;
    int key = 4 ;
    switch( key ) {
        case 0 : { test0() ; break ; }
        case 1 : { test1() ; break ; }
        case 2 : { test2() ; break ; }
        case 3 : { test3() ; break ; }
        default: { test4() ; break ; }
    }
    glEnd() ;
    glFlush() ;
}

void myIdle() {
    static clock_t last,current = last = clock() ;
    if ( (current - last) > (GLdouble)CLOCKS_PER_SEC/10 ) {
        last = current ;
        myDisplay() ;
    }
    current = clock() ;
}

void ProcessMenuEvent(int option) {
    switch ( option ) {
        case SHOW_NUM_100 : N = 100 ; break ;
        case SHOW_NUM_1000 : N = 1000 ; break ;
        case SHOW_NUM_10000 : N = 10000 ; break ;
        case SHOW_NUM_100000 : N = 100000 ; break ;
        default: break ;
    }
}

int main(int argc,char *argv[]) {
    glutInit(&argc,argv) ;
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE ) ;
    glutInitWindowSize(W,H) ;

    glutCreateWindow("RNG check") ;

    glutCreateMenu(&ProcessMenuEvent) ;
    glutAddMenuEntry("100points",SHOW_NUM_100) ;
    glutAddMenuEntry("1000points",SHOW_NUM_1000) ;
    glutAddMenuEntry("10000points",SHOW_NUM_10000) ;
    glutAddMenuEntry("100000points",SHOW_NUM_100000) ;
    glutAttachMenu(GLUT_RIGHT_BUTTON) ;

    glutDisplayFunc(&myDisplay) ;
    glutIdleFunc(&myIdle) ;
    myInit() ;

    glutMainLoop() ;
}