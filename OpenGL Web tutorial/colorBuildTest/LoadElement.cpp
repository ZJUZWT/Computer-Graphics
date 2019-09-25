//
// Created by MrKill on 2019/9/17.
//
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "LoadElement.h"

int createTexture(const char* fileName,GLint kind,unsigned int *texture,unsigned int colorMode,bool ifUpside) {
    glGenTextures(1,texture) ;
    glBindTexture(kind,*texture) ;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(ifUpside);

    int w,h,numChannels ;
    unsigned char *picture = stbi_load(fileName,&w,&h,&numChannels,0) ;

    if ( picture == nullptr )
        return FAIL_LOAD_PIC ;

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,colorMode,GL_UNSIGNED_BYTE,picture) ;
    glGenerateMipmap(GL_TEXTURE_2D) ;

    stbi_image_free(picture) ;

    return SUC_LOAD_ALL ;
}

void createVAOVNTE(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, unsigned int vSize, float *vertices, unsigned int eSize,unsigned int *indices) {
    glGenVertexArrays(1,VAO) ;
    glGenBuffers(1,VBO) ;
    glGenBuffers(1,EBO) ;

    glBindVertexArray(*VAO) ;
    glBindBuffer(GL_ARRAY_BUFFER,*VBO) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,*EBO) ;
    glBufferData(GL_ARRAY_BUFFER,vSize,vertices,GL_STATIC_DRAW) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,eSize,indices,GL_STATIC_DRAW) ;

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0) ;
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(sizeof(float)*3));
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(sizeof(float)*6));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER,0) ;
    glBindVertexArray(0) ;
}

void createVAOVNT(unsigned int *VAO, unsigned int *VBO, unsigned int vSize, float *vertices, unsigned int gap) {
    glGenVertexArrays(1,VAO) ;
    glGenBuffers(1,VBO) ;

    glBindVertexArray(*VAO) ;
    glBindBuffer(GL_ARRAY_BUFFER,*VBO) ;
    glBufferData(GL_ARRAY_BUFFER,vSize,vertices,GL_STATIC_DRAW) ;

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,gap,(void*)0) ;
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,gap,(void*)(sizeof(float)*3));
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,gap,(void*)(sizeof(float)*6));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER,0) ;
    glBindVertexArray(0) ;
}

void createVAOV(unsigned int *VAO, unsigned int *VBO, unsigned int vSize, float *vertices, unsigned int gap) {
    glGenVertexArrays(1,VAO) ;
    glGenBuffers(1,VBO) ;

    glBindVertexArray(*VAO) ;
    glBindBuffer(GL_ARRAY_BUFFER,*VBO) ;
    glBufferData(GL_ARRAY_BUFFER,vSize,vertices,GL_STATIC_DRAW) ;

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,gap,nullptr) ;
    glEnableVertexAttribArray(0) ;

    glBindBuffer(GL_ARRAY_BUFFER,0) ;
    glBindVertexArray(0);
}

void createVAOVN(unsigned int *VAO, unsigned int *VBO, unsigned int vSize, float *vertices, unsigned int gap) {
    glGenVertexArrays(1,VAO) ;
    glGenBuffers(1,VBO) ;

    glBindVertexArray(*VAO) ;
    glBindBuffer(GL_ARRAY_BUFFER,*VBO) ;
    glBufferData(GL_ARRAY_BUFFER,vSize,vertices,GL_STATIC_DRAW) ;

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,gap,nullptr) ;
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,gap,(void*)(sizeof(float)*3)) ;
    glEnableVertexAttribArray(0) ;
    glEnableVertexAttribArray(1) ;

    glBindBuffer(GL_ARRAY_BUFFER,0) ;
    glBindVertexArray(0);
}

void createVAOVT(unsigned int *VAO, unsigned int *VBO, unsigned int vSize, float *vertices, unsigned int gap) {}
