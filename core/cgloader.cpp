#include "cgrawmodel.hpp"
#include "cgloader.hpp"
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
*
* VBO optimization to make sure repeating vectors don't use up space
*
*/
void CGCore::Loader::BindIndicesBufferVBO(GLuint Indices[], GLuint ArraySize)
{
    GLuint VboID; 
    glGenBuffers(1,&VboID);
    VBOContainer.push_back(VboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)*ArraySize, Indices, GL_STATIC_DRAW);
}

void CGCore::Loader::CleanUp()
{
    
    for(GLuint n : VBOContainer) {
        glDeleteBuffers(1, &n);
    }
    
    for(GLuint n : VAOContainer) {
        glDeleteVertexArrays(1, &n);
    }
    
    VBOContainer.clear();
    VAOContainer.clear();
}

GLuint CGCore::Loader::CreateVAO()
{
    GLuint VaoID;
    glGenVertexArrays(1, &VaoID); // create the VAO
    VAOContainer.push_back(VaoID);
    glBindVertexArray(VaoID); // bind the VAO
    return VaoID;
}

CGCore::RawModel CGCore::Loader::LoadToVAO
(
    GLfloat Positions[], GLuint PosArrySize,
    GLuint Indices[], GLuint IndArrySize
)
{
    GLuint VaoID = CreateVAO();
    BindIndicesBufferVBO(Indices, IndArrySize); // Buffer Index - optimization
    StoreDataInAttrList(0, Positions, PosArrySize);
    UnbindVAO();
    CGCore::RawModel ret = CGCore::RawModel(VaoID, IndArrySize);
    return ret;
}

void CGCore::Loader::StoreDataInAttrList(GLuint AttrNumber, GLfloat Data[], GLuint DataSize)
{
    GLuint VboID; 
    glGenBuffers(1,&VboID);
    VBOContainer.push_back(VboID);
    glBindBuffer(GL_ARRAY_BUFFER, VboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*DataSize, Data, GL_STATIC_DRAW);
    glVertexAttribPointer(AttrNumber, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // write to VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind current VBO
}

void CGCore::Loader::UnbindVAO()
{
    glBindVertexArray(0); // Unbind any VAOs
}