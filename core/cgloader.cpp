#include "cgrawmodel.hpp"
#include "cgloader.hpp"
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// TODO: Keep VAOs and VBOs in a list for proper memory management 

GLuint CGCore::Loader::CreateVAO()
{
    GLuint VaoID;
    glGenVertexArrays(1, &VaoID); // create the VAO
    glBindVertexArray(VaoID); // bind the VAO
    return VaoID;
}

RawModel CGCore::Loader::LoadToVAO(GLfloat Positions[], GLuint ArraySize)
{
    GLuint VaoID = CreateVAO();
    StoreDataInAttrList(0, Positions, ArraySize);
    UnbindVAO();
    return RawModel(VaoID, ArraySize / 3);
}

void CGCore::Loader::StoreDataInAttrList(GLuint AttrNumber, GLfloat Data[], GLuint DataSize)
{
    GLuint VboID; 
    glGenBuffers(1,&VboID);
    glBindBuffer(GL_ARRAY_BUFFER, VboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*DataSize, Data, GL_STATIC_DRAW);
    glVertexAttribPointer(AttrNumber, 3, GL_FLOAT, GL_FALSE, 0, 0); // write to VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind current VBO
}

void CGCore::Loader::UnbindVAO()
{
    glBindVertexArray(0); // Unbind any VAOs
}