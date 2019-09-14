#include "SDL.h"
#include <iostream>
#include <fstream>

void Mesh::readFile(const char *fileName) {
    std::ifstream file(fileName) ;
    if ( !file.is_open() ) {
        printf( "Error to open this file. filename:%s\n" , fileName ) ;
        file.close() ;
        return ;
    }
    file >> this->numVerts >> this->numNorms >> this->numFaces ;
    this->pt = (Point3*)malloc( sizeof(Point3)*numVerts ) ;
    this->norm = (Vector3*)malloc( sizeof(Vector3)*numNorms ) ;
    this->face = (Face*)malloc( sizeof(Face)*numFaces ) ;
    for ( int i = 0 ; i < numVerts ; i++ )
        file >> pt[i].x >> pt[i].y >> pt[i].z ;
    for ( int i = 0 ; i < numNorms ; i++ )
        file >> norm[i].x >> norm[i].y >> norm[i].z ;
    for ( int i = 0 ; i < numFaces ; i++ ) {
        file >> this->face[i].nVerts ;
        this->face[i].vert = (VertexID*) malloc(sizeof(VertexID)*this->face[i].nVerts) ;
        for ( int j = 0 ; j < this->face[i].nVerts ; j++ )
            file >> this->face[i].vert[j].vertIndex ;
        for ( int j = 0 ; j < this->face[i].nVerts ; j++ )
            file >> this->face[i].vert[j].normIndex ;
    }
    file.close() ;
    printf( "Success to read this file. filename:%s\n" , fileName ) ;
}

void Mesh::draw() {
    for ( int i = 0 ; i < numFaces ; i++ ) {
        int in ;
        int iv ;

//        glBegin(GL_LINE_LOOP) ;
//        for ( int j = 0 ; j < this->face[i].nVerts ; j++ ) {
//            in = this->face[i].vert[j].normIndex ;
//            iv = this->face[i].vert[j].vertIndex ;
//            glNormal3f(norm[in].x,norm[in].y,norm[in].z) ;
//            glVertex3f(pt[iv].x,pt[iv].y,pt[iv].z) ;
//        }
//        in = this->face[i].vert[0].normIndex ;
//        iv = this->face[i].vert[0].vertIndex ;
//        glNormal3f(norm[in].x,norm[in].y,norm[in].z) ;
//        glVertex3f(pt[iv].x,pt[iv].y,pt[iv].z) ;
//        glEnd() ;

        glBegin(GL_POLYGON) ;
        for ( int j = 0 ; j < this->face[i].nVerts ; j++ ) {
            in = this->face[i].vert[j].normIndex ;
            iv = this->face[i].vert[j].vertIndex ;
            glNormal3f(norm[in].x,norm[in].y,norm[in].z) ;
            glVertex3f(pt[iv].x,pt[iv].y,pt[iv].z) ;
        }
        in = this->face[i].vert[0].normIndex ;
        iv = this->face[i].vert[0].vertIndex ;
        glNormal3f(norm[in].x,norm[in].y,norm[in].z) ;
        glVertex3f(pt[iv].x,pt[iv].y,pt[iv].z) ;
        glEnd() ;
    }
}