//
// Created by MrKill on 2019/9/17.
//

#ifndef TRANSFORMATIONSTEST_LOADELEMENT_H
#define TRANSFORMATIONSTEST_LOADELEMENT_H

//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define SUC_LOAD_ALL 0
#define FAIL_LOAD_PIC 1

int createTexture(const char* fileName,GLint kind,unsigned int *texture,unsigned int colorMode,bool ifUpside) ;
void createVAOVNTE(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, unsigned int vSize, float *vertices, unsigned int eSize,unsigned int *indices) ;
void createVAOVNT(unsigned int *VAO, unsigned int *VBO, unsigned int vSize, float *vertices, unsigned int gap) ;
void createVAOV(unsigned int *VAO, unsigned int *VBO, unsigned int vSize, float *vertices, unsigned int gap) ;
void createVAOVN(unsigned int *VAO, unsigned int *VBO, unsigned int vSize, float *vertices, unsigned int gap) ;
void createVAOVT(unsigned int *VAO, unsigned int *VBO, unsigned int vSize, float *vertices, unsigned int gap) ;

#endif //TRANSFORMATIONSTEST_LOADELEMENT_H
