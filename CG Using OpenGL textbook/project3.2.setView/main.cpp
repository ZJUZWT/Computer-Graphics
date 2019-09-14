#include <GL/glut.h>
#include <cmath>
#include <cstdio>

const GLdouble pi = 3.1415926 ;
const GLint W = 512 ;
const GLint H = 512 ;

GLdouble leftBorder = -5.0 ;
GLdouble bottomBorder = -0.5 ;
GLdouble dLRBorder = 10.0 ;
GLdouble dUDBorder = 2.0 ;
GLdouble offsetBorder = 0.03 ;
const GLdouble zoomFactor = 1.2 ;

void setViewport(GLint left,GLint right,GLint bottom,GLint top) {
    glViewport(left,bottom,right-left,top-bottom) ;
}

void setWindow(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top) {
//    setViewport(W/2,W,H/2,H) ;
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
//    setViewport(W/2,W,H/2,H) ;
    gluOrtho2D(left,right,bottom,top) ;
//    setViewport(W/2,W,H/2,H) ;
}

GLdouble f(GLdouble x) {
    return sin(pi*x)/pi/x ;
}

void drawLine(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2) {
    glBegin(GL_LINES) ;
    glVertex2f( x1 , y1 ) ;
    glVertex2f( x2 , y2 ) ;
    glEnd() ;
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT) ;

    for ( int i = 0 ; i < 2 ; i++ ) {
        for ( int j = 0 ; j < 2 ; j++ ) {
            glViewport( W/2*i , H/2*j , W/2 , H/2 ) ;
            //    glMatrixMode(GL_MODELVIEW) ;
            //    glLoadIdentity() ;
            glBegin(GL_LINE_STRIP);
            for (GLdouble x = leftBorder; x <= leftBorder + dLRBorder; x += 0.01) {
                if (x == 0.0) glVertex2f(0.0, 1.0); else glVertex2f(x, f(x));
                //        if ( fabs(x - (GLint)x) < 1e-4 )
            }
            glEnd() ;
            drawLine(0,bottomBorder,0,bottomBorder+dUDBorder) ;
            drawLine(leftBorder,0,leftBorder+dLRBorder,0) ;
        }
    }
    glFlush() ;
}

const int LEFT_KEY = 100 ;
const int UP_KEY = 101 ;
const int RIGHT_KEY = 102 ;
const int DOWN_KEY = 103 ;

void mySpecialKey(int key,int x,int y) {
    switch ( key ) {
        case LEFT_KEY : leftBorder -= dLRBorder*offsetBorder ;   break ;
        case RIGHT_KEY : leftBorder += dLRBorder*offsetBorder ;  break ;
        case UP_KEY : bottomBorder += dUDBorder*offsetBorder ;   break ;
        case DOWN_KEY : bottomBorder -= dUDBorder*offsetBorder ; break ;
        default: return ;
    }
    setWindow(leftBorder,leftBorder+dLRBorder,bottomBorder,bottomBorder+dUDBorder) ;
    glutPostRedisplay() ;
}

void myMouse(int button,int state,int x,int y) {
    if ( state == GLUT_DOWN ) {
        switch ( button ) {
            case GLUT_LEFT_BUTTON :
                leftBorder += (GLdouble)x/W*(1-1/zoomFactor)*dLRBorder ;
                bottomBorder += (GLdouble)(H-y)/H*(1-1/zoomFactor)*dUDBorder ;
                dUDBorder /= zoomFactor ;
                dLRBorder /= zoomFactor ;
                break ;
            case GLUT_RIGHT_BUTTON :
                dUDBorder *= zoomFactor ;
                dLRBorder *= zoomFactor ;
                leftBorder -= (GLdouble)x/W*(1-1/zoomFactor)*dLRBorder ;
                bottomBorder -= (GLdouble)(H-y)/H*(1-1/zoomFactor)*dUDBorder ;
                break ;
            default: return ;
        }
        setWindow(leftBorder,leftBorder+dLRBorder,bottomBorder,bottomBorder+dUDBorder) ;
        glutPostRedisplay() ;
    }
}

void myInit() {
    glClearColor( 1.0 , 1.0 , 1.0 , 0.0 ) ;
    glColor3f( 0.0 , 0.0 , 0.0 ) ;
    glLineWidth( 1.0 ) ;
}

int main(int argc,char**argv) {
    glutInit(&argc,argv) ;
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE ) ;
    glutInitWindowSize(W,H) ;
    glutInitWindowPosition(100,100) ;
    glutCreateWindow("test function view") ;
    glutDisplayFunc(&myDisplay) ;

    glutSpecialFunc(&mySpecialKey) ;
    glutMouseFunc(&myMouse) ;

    myInit() ;
    setWindow(leftBorder,leftBorder+dLRBorder,bottomBorder,bottomBorder+dUDBorder) ;
//    setViewport(W/2,W,H/2,H) ;
//    setWindow(leftBorder*2,(leftBorder+dLRBorder)*2,(bottomBorder)*2,(bottomBorder+dUDBorder)*2) ;
//    setViewport(0,W,0,H) ;

    glutMainLoop() ;
    return 0 ;
}