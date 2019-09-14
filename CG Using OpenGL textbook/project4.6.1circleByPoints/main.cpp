#include <GL/glut.h>
#include <cstdio>
#include <cmath>

#include "Coordinate.h"

Coordinate *List = (Coordinate *)malloc(4*sizeof(Coordinate));
Coordinate Mouse = Coordinate(0.0,0.0,1);
GLint num = 0 ;

const GLint W = 756 ;
const GLint H = 756 ;
const GLdouble pi = 3.1415926 ;
const GLdouble black[3] = {0.0,0.0,0.0};
const GLdouble red[3] = {1.0,0.0,0.0};
const GLdouble blue[3] = {0.0,0.0,1.0};

void myDisplay() ;
void myIdle() ;
void myInit() ;
void myMouse(GLint button,GLint state,GLint x,GLint y) ;
void myPassiveMotion(GLint x,GLint y) ;
void setWindow(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top) ;
void setViewport(GLint left,GLint right,GLint bottom,GLint top) ;
void drawDot(Coordinate point,GLdouble r,GLdouble g,GLdouble b) ;
void drawLine(Coordinate point1,Coordinate point2,GLdouble r,GLdouble g,GLdouble b) ;
void drawLine(Coordinate point,Coordinate vector,GLdouble r,GLdouble g,GLdouble b) ;
void drawCircle(Coordinate point,GLdouble radius,GLdouble r,GLdouble g,GLdouble b) ;

void solveAll() ;
void solveOutCircle() ;
void solveInCircle() ;
Coordinate solveIntersect(Coordinate point1,Coordinate vector1,Coordinate point2,Coordinate vector2) ;
GLdouble getArea(GLdouble a,GLdouble b,GLdouble c) ;
GLdouble getCircumference(GLdouble a,GLdouble b,GLdouble c) ;

int main(int argc,char**argv) {

    glutInit(&argc,argv) ;
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE ) ;
    glutInitWindowPosition(100,100) ;
    glutInitWindowSize(W,H) ;
    glutCreateWindow("circle check") ;

    myInit() ;

    glutDisplayFunc(&myDisplay) ;
    glutMouseFunc(&myMouse) ;
    glutPassiveMotionFunc(&myPassiveMotion) ;

    setWindow(0,W,0,H) ;
    setViewport(0,W,0,H) ;

    glutMainLoop() ;
    return 0;
}

void solveAll() {
    for ( int i = 1 ; i <= num ; i++ ) {
        drawLine(List[i],List[i%num+1],black[0],black[1],black[2]) ;
    }
    solveOutCircle() ;
    solveInCircle() ;
}

void solveOutCircle() {
    Coordinate vectorAB = Coordinate( List[1] , List[2] ) ;//Vector AB = ( x1 , y1 )
    Coordinate vectorAC = Coordinate( List[1] , List[3] ) ;//Vector AC = ( x2 , y2 )
    Coordinate vectorTAB = vectorAB.transVertical() ;
    Coordinate VectorTAC = vectorAC.transVertical() ;

    Coordinate centerOutCircle = solveIntersect(
            Coordinate::midPoint(List[1],List[2]),vectorTAB,
            Coordinate::midPoint(List[1],List[3]),VectorTAC) ;

//    drawLine( Coordinate::midPoint(List[1],List[2]) , vectorTAB , red[0] , red[1] , red[2] ) ;
//    drawLine( Coordinate::midPoint(List[1],List[3]) , VectorTAC , red[0] , red[1] , red[2] ) ;
    GLdouble radius = sqrt( pow(centerOutCircle.x-List[1].x,2) + pow(centerOutCircle.y-List[1].y,2) ) ;
    drawCircle( centerOutCircle , radius , red[0] , red[1] , red[2] ) ;
    drawDot( centerOutCircle , red[0] , red[1] , red[2] ) ;
}

void solveInCircle() {
    Coordinate vectorABis = Coordinate( List[1] , List[2] ).transStandard() + Coordinate( List[1] , List[3] ).transStandard() ;
    Coordinate vectorBBis = Coordinate( List[2] , List[1] ).transStandard() + Coordinate( List[2] , List[3] ).transStandard() ;

    Coordinate centerInCircle = solveIntersect(List[1],vectorABis,List[2],vectorBBis) ;

    GLdouble
        a = (List[1]-List[2]).length() ,
        b = (List[2]-List[3]).length() ,
        c = (List[3]-List[1]).length() ;
    GLdouble C = getCircumference(a,b,c) ;
    GLdouble S = getArea(a,b,c) ;
    GLdouble radius = 2*S/C ;

//    printf( "Check! %.3lf %.3lf %.3lf\n" , radius , a , b , c ) ;

//    drawLine( List[1] , vectorABis*100 , blue[0] , blue[1] , blue[2] ) ;
//    drawLine( List[2] , vectorBBis*100 , blue[0] , blue[1] , blue[2] ) ;
    drawCircle( centerInCircle , radius , blue[0] , blue[1] , blue[2] ) ;
    drawDot( centerInCircle , blue[0] , blue[1] , blue[2] ) ;
}

Coordinate solveIntersect(Coordinate point1,Coordinate vector1,Coordinate point2,Coordinate vector2) {
    Coordinate vector3 = Coordinate(point2,point1) ;
    Coordinate vector1T = vector1.transVertical() ;

    GLdouble coefficient = (vector3*vector1T) / (vector2*vector1T) ;
    return vector2*coefficient+point2 ;
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT) ;
    for ( int i = 1 ; i <= num ; i++ )
        drawDot(List[i],black[0],black[1],black[2]) ;
    if ( num == 3 ) solveAll() ;
    else {
        switch ( num ) {
            case 1 :
                break ;
            case 2 :
                List[3] = Mouse ;
                drawLine(List[1],List[2],0.0,0.0,0.0) ;
                drawLine(List[1],Mouse  ,0.0,0.0,0.0) ;
                solveOutCircle() ;
                solveInCircle() ;
                break ;
            default:
                break ;
        }
        drawLine(List[num],Mouse,0.0,0.0,0.0) ;
    }
    glFlush() ;
}

void drawLine(Coordinate point1,Coordinate cor,GLdouble r,GLdouble g,GLdouble b) {
    glColor3f(r,g,b);
    glBegin(GL_LINES) ;
    if ( cor.mode == 1 ) {
        Coordinate point2 = cor ;
        glVertex2f( point1.x , point1.y ) ;
        glVertex2f( point2.x , point2.y ) ;
    }
    if ( cor.mode == 0 ) {
        Coordinate vector1 = cor ;
        glVertex2f( point1.x+vector1.x , point1.y+vector1.y ) ;
        glVertex2f( point1.x-vector1.x , point1.y-vector1.y ) ;
    }
    glEnd() ;
}

void drawDot(Coordinate point,GLdouble r,GLdouble g,GLdouble b) {
    glColor3f(r,g,b);
    glBegin(GL_POINTS) ;
    glVertex2f(point.x,point.y) ;
    glEnd() ;
}

void drawCircle(Coordinate point,GLdouble radius,GLdouble r,GLdouble g,GLdouble b) {
    glColor3f(r,g,b);
    glBegin(GL_LINE_STRIP) ;
    for ( GLdouble theta = 0 ; theta <= 2*pi ; theta += 0.01 ) {
        glVertex2f( radius*cos(theta)+point.x , radius*sin(theta)+point.y ) ;
    }
    glEnd() ;
}

void setWindow(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top) {
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    gluOrtho2D(left,right,bottom,top) ;
}

void setViewport(GLint left,GLint right,GLint bottom,GLint top) {
    glViewport(left,bottom,right-left,top-bottom) ;
}

void myInit() {
    glClearColor(1.0,1.0,1.0,0.0) ;
    glColor3f(black[0],black[1],black[2]) ;
    glPointSize(5.0) ;
    glLineWidth(1.0) ;
}

void myMouse(GLint button,GLint state,GLint x,GLint y) {
    if ( button != GLUT_LEFT_BUTTON ) return ;
    if ( state != GLUT_DOWN ) return ;
    if ( num == 3 ) glClear(GL_COLOR_BUFFER_BIT) , num = 0 ;
    num++ ;

    Mouse.x = x ; Mouse.y = H-y ;
    List[num].x = x ; List[num].y = H-y ; List[num].mode = 1 ;
    drawDot(List[num],black[0],black[1],black[2]) ;
    glutPostRedisplay() ;
}

void myPassiveMotion(GLint x,GLint y) {
    if ( num % 3 == 0 ) return ;
    Mouse.x = x ; Mouse.y = H-y ;
    glutPostRedisplay() ;
}

GLdouble getArea(GLdouble a,GLdouble b,GLdouble c) {
    GLdouble p = (a+b+c)/2 ;
    return sqrt( p*(p-a)*(p-b)*(p-c) ) ;
}

GLdouble getCircumference(GLdouble a,GLdouble b,GLdouble c) {
    return a+b+c ;
}