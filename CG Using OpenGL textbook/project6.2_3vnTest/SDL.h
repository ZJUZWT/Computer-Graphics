#ifndef _SDL
#define _SDL

#include <cstdio>
#include <GL/gl.h>

class Point3 {
public:
    GLdouble x , y , z ;
    Point3(GLdouble x,GLdouble y,GLdouble z) {
        this->x = x ; this->y = y ; this->z = z ;
    }
};

class Vector3 {
public:
    GLdouble x , y , z ;
    Vector3(GLdouble x,GLdouble y,GLdouble z) {
        this->x = x ; this->y = y ; this->z = z ;
    }
};

class VertexID {
public:
    int vertIndex ;
    int normIndex ;
};

class Face{
public:
    int nVerts ;
    VertexID *vert ;
    Face() { nVerts = 0 ; vert = nullptr ; }
    ~Face() { delete[] vert ; nVerts = 0 ; }
};

class Mesh{
private:
    int numVerts ;
    Point3 *pt ;
    int numNorms ;
    Vector3 *norm ;
    int numFaces ;
    Face *face ;
    void readFile(const char *fileName) ;
    void readFunc(const char *fileName) ;
    void drawFile(int mode) ;
    void drawFunc(int mode) ;

public:
    Mesh(const char *fileName,int mode) {
        numVerts = 0 ; numNorms = 0 ; numFaces = 0 ;
        pt = nullptr ; norm = nullptr ; face = nullptr ;
        switch (mode) {
            case 1 :{
                readFile(fileName) ;
                break ;
            }
            case 2 :{
                readFunc(fileName) ;
                break ;
            }
            default:
                break ;
        }
    } ;
    ~Mesh() { delete[] pt ; delete[] norm ; delete[] face ; numFaces = 0 ; numNorms = 0 ; numVerts = 0 ; }
    void draw(int drawMode,int objectMode) ;
} ;

#endif



