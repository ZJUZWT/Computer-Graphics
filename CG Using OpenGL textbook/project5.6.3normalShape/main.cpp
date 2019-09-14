#include <GL/freeglut.h>
#include <cstdio>
#include <cmath>
#include <ctime>

const GLint W = 756 ;
const GLint H = 756 ;
const GLdouble pi = 3.1415926 ;
const GLdouble black[3] = {0.0,0.0,0.0};
const GLdouble red[3] = {1.0,0.0,0.0};
const GLdouble green[3] = {0.0,1.0,0.0};
const GLdouble blue[3] = {0.0,0.0,1.0};
const GLdouble radii = 18 ;
GLdouble x = 0 , t = 0 , direction = 1 ;

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

void drawCoordinate() ;
void drawLine(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2,GLdouble r,GLdouble g,GLdouble b) ;
void drawDot(GLdouble x,GLdouble y,GLdouble r,GLdouble g,GLdouble b) ;
void drawHex(GLdouble x,GLdouble y,GLdouble radius,GLdouble r,GLdouble g,GLdouble b) ;

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

const GLdouble sigma = 0.18 ;
const GLdouble sigma2 = sigma*sigma ;
GLdouble normalDis(GLdouble x) {
    return 1/sqrt(2*pi)/sigma*exp( -pow(x-0.5,2) / (2*sigma2) ) ;
}

void myIdle() {
    t = clock() ;
    if ( (t-x) > CLOCKS_PER_SEC/144 ) {
        static GLint num = 0 ;
        num++ ;
//        popCT() ;
//        pushCT() ;
//        gluLookAt(cos(pi*num/500),0,sin(pi*num/500), 0, 0, 0, 1, 1, 0);
//        printf("(%.3lf,%.3lf)\n",cos(pi*num/1000),sin(pi*num/1000)) ;
        x = t ;
    }
    myDisplay() ;
}

const GLint xNum = 100 ;
const GLint yNum = 100 ;

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT ) ;
//    glutSolidTorus(60,120,100,200) ;
    glutWireTorus(120,756/2-120,16,200) ;
    drawCoordinate() ;
    glutSwapBuffers() ;
}

void drawCoordinate() {
    glColor3f( red[0] , red[1] , red[2] ) ;
    glBegin(GL_LINES) ;
    glVertex3f(0,0,0) ;
    glVertex3f(1000,0,0) ;
    glEnd() ;
    glColor3f( green[0] , green[1] , green[2] ) ;
    glBegin(GL_LINES) ;
    glVertex3f(0,0,0) ;
    glVertex3f(0,1000,0) ;
    glEnd() ;
    glColor3f( blue[0] , blue[1] , blue[2] ) ;
    glBegin(GL_LINES) ;
    glVertex3f(0,0,0) ;
    glVertex3f(0,0,1000) ;
    glEnd() ;
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

    glBegin(GL_LINE_STRIP) ;
//    glMatrixMode(GL_MODELVIEW) ;
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
//    GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f}; // gray
//    GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
//    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
//    GLfloat mat_shininess[] = {80.0f};
//    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
//    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
//    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
//    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
//    // set the light source properties
//    GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
//    GLfloat light_position[] = {0.0f, 0.0f, -1.0f, 0.0f};
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    glClearColor(1.0,1.0,1.0,0.0) ;
    glColor3f(black[0],black[1],black[2]) ;
    glPointSize(5.0) ;
    glLineWidth(1.0) ;
    setWindow(-W/2,W/2,-H/2,H/2,-400,400) ;
//    setViewport(0,W,0,H) ;
    initCT() ;
//    pushCT() ;
//    pushCT() ;

//    glEnable(GL_LIGHTING); // enable the light source
//    glEnable(GL_LIGHT0);
//    glShadeModel(GL_SMOOTH);
//    glEnable(GL_DEPTH_TEST); // for hidden surface removal
//    glEnable(GL_NORMALIZE); // normalize vectors for proper shading
}

void initCT() {
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity() ;
//    gluLookAt(0,sin(pi/3),cos(pi/3),0,0,0,0,1,0) ;
    gluLookAt(cos(pi/4),sin(pi/3),cos(pi/4),0,0,0,0,1,0) ;
//    gluLookAt(0,sin(pi/4),cos(pi/4),0,0,0,0,sin(3*pi/4),cos(3*pi/4)) ;
//    gluLookAt(0,sin(pi/4),cos(pi/4),0,0,0,1,0,0) ;
//    gluLookAt(0,0,1,0,0,0,1,0,0) ;
//    gluLookAt(0,0,0,0,0,0,0,1,0) ;
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