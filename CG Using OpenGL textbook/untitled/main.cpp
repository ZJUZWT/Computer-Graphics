#include <GL/glut.h>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstdlib>

// 太阳、地球和月亮
// 假设每个月都是12天
// 一年12个月，共是360天
static double day = 200; // day的变化：从0到359

double CalFrequency()
{
    static int count;
    static double save;
    static clock_t last, current;
    double timegap;

    ++count;
    if( count <= 50 )
        return save;
    count = 0;
    last = current;
    current = clock();
    timegap = (current-last)/(double)CLK_TCK;
    save = 50.0/timegap;
    return save;
}

//void myDisplay(void)
//{
//    double FPS = CalFrequency();
//    printf("FPS = %f\n", FPS);
//
//    glEnable(GL_DEPTH_TEST);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(75, 1, 1, 4000000);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(0, -2000000, 2000000, 0, 0, 0, 0, 0, 1);
//
//    // 绘制红色的“太阳”
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glutSolidSphere(696000, 200, 200);
//    // 绘制蓝色的“地球”
//    glColor3f(0.0f, 0.0f, 1.0f);
//    glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
//    glTranslatef(1500000, 0.0f, 0.0f);
//    glutSolidSphere(159450, 200, 200);
//    // 绘制黄色的“月亮”
//    glColor3f(1.0f, 1.0f, 0.0f);
//    glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
//    glTranslatef(380000, 0.0f, 0.0f);
//    glutSolidSphere(43450, 200, 200);
//
//    glFlush();
//    glutSwapBuffers();
//}
//
//void myIdle(void)
//{
//    day += 0.1 ;
//    if( day >= 360 )
//        day = 0;
//    myDisplay();
//}

//double offset = 0;
//const int numPoint = 10;
//const GLdouble pi = 3.141592f;
//const GLdouble r = 0.5f;
//
////！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！双缓冲
//
//void myDisplay() {
//    double FPS = CalFrequency();
//    printf("FPS = %f\n", FPS);
//
//    glColor3f(0, 0, 0);
//    glBegin(GL_POLYGON);
//    for (int i = 0; i < numPoint; i++) {
//        glVertex2f(r * cos(2 * pi / numPoint * i), r * sin(2 * pi / numPoint * i) + sin(offset * pi) / 2);
//    }
//    glEnd();
//
//    offset += 0.001;
//
//    glColor3f(1, 1, 1);
//    glBegin(GL_POLYGON);
//    for (int i = 0; i < numPoint; i++) {
//        glVertex2f(r * cos(2 * pi / numPoint * i), r * sin(2 * pi / numPoint * i) + sin(offset * pi) / 2);
//    }
//    glEnd();
//    glFlush();
//
//    glutSwapBuffers();
//}
//
//void myIdle() {
//    if (offset > 2) offset -= 2;
//    myDisplay();
//}
//
//int main(int argc, char *argv[]) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(600, 600);
//    glutCreateWindow("test");
//    glutDisplayFunc(&myDisplay);
//    glutIdleFunc(&myIdle);
//    glutMainLoop();
//    return 0;
//}

//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！双缓冲


//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！单缓冲

//void myDisplay() {
//    double FPS = CalFrequency();
//    printf("FPS = %f\n", FPS) ;
//
//    glColor3f(0,0,0) ;
//    glBegin(GL_POLYGON);
//    for (int i = 0; i<numPoint; i++) {
//        glVertex2f(r*cos(2 * pi / numPoint*i), r*sin(2 * pi / numPoint*i)+sin(offset*pi)/2);
//    }
//    glEnd() ;
//
//    offset += 0.001 ;
//
//    glColor3f(1,1,1) ;
//    glBegin(GL_POLYGON);
//    for (int i = 0; i<numPoint; i++) {
//        glVertex2f(r*cos(2 * pi / numPoint*i), r*sin(2 * pi / numPoint*i)+sin(offset*pi)/2);
//    }
//    glEnd();
//    glFlush();
//}
//
//void myIdle() {
//    if ( offset > 2 ) offset -= 2 ;
//    myDisplay() ;
//}
//
//int main(int argc, char *argv[])
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(600, 600);
//    glutCreateWindow("test");
//    glutDisplayFunc(&myDisplay);
//    glutIdleFunc(&myIdle);
//    glutMainLoop();
//    return 0;
//}

//#define TWO_PI 6.28318530718f
//#define W 512
//#define H 512
//#define N 64
//#define MAX_STEP 8
//#define MAX_DISTANCE 2.0f
//#define EPSILON 1e-6f
//
//float circleSDF(float x, float y, float cx, float cy, float r) {
//    float ux = x - cx, uy = y - cy;
//    return sqrtf(ux * ux + uy * uy) - r;
//}
//
//float trace(float ox, float oy, float dx, float dy) {
//    float t = 0.0f;
//    for (int i = 0; i < MAX_STEP && t < MAX_DISTANCE; i++) {
//        float sd = circleSDF(ox + dx * t, oy + dy * t, 0.5f, 0.5f, 0.1f);
//        if (sd < EPSILON)
//            return 2.0f;
//        t += sd;
//    }
//    return 0.0f;
//}
//
//float sample(float x, float y) {
//    float sum = 0.0f;
//    for (int i = 0; i < N; i++) {
////         float a = TWO_PI * rand() / RAND_MAX;
////         float a = TWO_PI * i / N;
//        float a = TWO_PI * (i + (float)rand() / RAND_MAX) / N;
//        sum += trace(x, y, cosf(a), sinf(a));
//    }
//    return sum / N;
//}
//
//int gap = 1 ;
//
//void myDisplay() {
//
//    printf( "FPS = %.3lf\n" , CalFrequency() ) ;
//
//    glClear(GL_COLOR_BUFFER_BIT);
//    glPointSize(0.01f);
//    glBegin(GL_POINTS);
//    for (int y = gap; y < H; y+=gap )
//        for (int x = gap; x < W; x+=gap ) {
//            int color = (int)(fminf(sample((float)x / W, (float)y / H) * 255.0f, 255.0f)) ;
////            GLdouble
////                rcolor = (GLdouble)rand()/32766 ,
////                gcolor = (GLdouble)rand()/32766 ,
////                bcolor = (GLdouble)rand()/32766 ;
//
////            printf( "(%.2lf,%.2lf,%.2lf)\n" , rcolor , gcolor , bcolor ) ;
//
//            glColor3f( color/255.0 , color/255.0/2 , color/255.0/2 ) ;
////            glColor3f( rcolor , gcolor , bcolor ) ;
//            glVertex2f( (GLdouble)x/W*2-1 , (GLdouble)y/H*2-1 ) ;
////            printf( "(%d,%d):%d\n" , x , y , color ) ;
////            glVertex2f( 0 , 0 ) ;
//         }
//    glEnd() ;
//    glFlush() ;
//
//    glutSwapBuffers() ;
//}
//
//void myIdle() {
//    myDisplay() ;
//}
//
//int main(int argc, char *argv[]) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(W,H);
//    glutCreateWindow("test");
//    glutDisplayFunc(&myDisplay);
////    glutIdleFunc(&myIdle) ;
//    glutMainLoop();
//    return 0;
//}

#define TWO_PI 6.28318530718f
#define W 512
#define H 512
#define N 128
#define MAX_STEP 128
#define MAX_DISTANCE 2.0f
#define EPSILON 1e-3f

typedef struct { float sd, emissive; } Result;

float circleSDF(float x, float y, float cx, float cy, float r) {
    float ux = x - cx, uy = y - cy;
    return sqrtf(ux * ux + uy * uy) - r;
}

Result unionOp(Result a, Result b) {
    return a.sd < b.sd ? a : b;
}

Result scene(float x, float y) {
    Result r = { circleSDF(x, y, 0.5f, 0.5f, 0.1f), 2.0f };
    return r;
}

//Result scene(float x, float y) {
//    Result r1 = { circleSDF(x, y, 0.3f, 0.3f, 0.10f), 2.0f };
//    Result r2 = { circleSDF(x, y, 0.3f, 0.7f, 0.05f), 2.0f };
//    Result r3 = { circleSDF(x, y, 0.7f, 0.5f, 0.10f), 0.0f };
//    return unionOp(unionOp(r1, r2), r3);
//}


float trace(float ox, float oy, float dx, float dy) {
    float t = 0.0f;
    for (int i = 0; i < MAX_STEP && t < MAX_DISTANCE; i++) {
        Result r = scene(ox + dx * t, oy + dy * t);
        if (r.sd < EPSILON)
            return r.emissive;
        t += r.sd;
    }
    return 0.0f;
}

float sample(float x, float y) {
    float sum = 0.0f;
    for (int i = 0; i < N; i++) {
//         float a = TWO_PI * rand() / RAND_MAX;
//         float a = TWO_PI * i / N;
        float a = TWO_PI * (i + (float)rand() / RAND_MAX) / N;
        sum += trace(x, y, cosf(a), sinf(a));
    }
    return sum / N;
}

GLdouble gap = 1.0 ;

void myDisplay() {

    printf( "FPS = %.3lf\n" , CalFrequency() ) ;

    glClear(GL_COLOR_BUFFER_BIT);
//    glPointSize(0.01f);
    glBegin(GL_POINTS);
    for (GLdouble y = gap; y < H; y+=gap )
        for (GLdouble x = gap; x < W; x+=gap ) {
            int color = (int)(fminf(sample((float)x / W, (float)y / H) * 255.0f, 255.0f)) ;

            glColor3f( color/255.0 , color/255.0/2 , color/255.0/2 ) ;
            glVertex2f( x/W*2-1 , y/H*2-1 ) ;
        }
    glEnd() ;
    glFlush() ;
}

void myIdle() {
    myDisplay() ;
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(W,H);
    glutCreateWindow("test");
    glutDisplayFunc(&myDisplay);
//    glutIdleFunc(&myIdle) ;
    glutMainLoop();
    return 0;
}