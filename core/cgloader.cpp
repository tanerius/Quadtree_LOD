#include "cgrawmodel.hpp"
#include "cgtexture.hpp"
#include "cgloader.hpp"

#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <png.h> // Ability to read png files for textures
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
*
* VBO optimization to make sure repeating vectors don't use up space
*
*/
void CGCore::Loader::BindIndicesBufferVBO(const GLuint Indices[], GLuint ArraySize)
{
    GLuint VboID; 
    glGenBuffers(1,&VboID);
    VBOContainer.push_back(VboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*ArraySize, Indices, GL_STATIC_DRAW);
}

void CGCore::Loader::CleanUp()
{
    
    for(GLuint n : VBOContainer) {
        glDeleteBuffers(1, &n);
    }
    
    for(GLuint n : VAOContainer) {
        glDeleteVertexArrays(1, &n);
    }

    for(CGCore::Texture* n : TextureContainer)
    {
        delete n;
        n = 0;
    }
    
    VBOContainer.clear();
    VAOContainer.clear();
    TextureContainer.clear();
}

void CGCore::Loader::CreateBindVAO()
{
    GLuint VaoID;
    glGenVertexArrays(1, &VaoID); // create the VAO
    VAOContainer.push_back(VaoID);
    glBindVertexArray(VaoID); // bind the VAO
}

CGCore::RawModel* CGCore::Loader::LoadToVAO
(
    const GLfloat VertexData[], GLuint PosArrySize,
    const GLuint Indices[], GLuint IndArrySize,
    const GLfloat TextureUV[], GLuint TCArrySize
)
{
    BindIndicesBufferVBO(Indices, IndArrySize); // Buffer Index - optimization
    StoreDataInAttrList(0, 3, VertexData, PosArrySize);
    StoreDataInAttrList(1, 2, TextureUV, TCArrySize);
    UnbindVAO();
    CGCore::RawModel* ret = new CGCore::RawModel(VAOContainer[0], IndArrySize);
    return ret;
}


// Creates a VBO and loads it with data and returns the name
GLuint CGCore::Loader::LoadToVBO(const GLfloat DataArray[], const GLuint DataSize)
{
    //printf("Data Loader\n");
    GLuint VboID; 
    glGenBuffers(1,&VboID);
    VBOContainer.push_back(VboID);
    glBindBuffer(GL_ARRAY_BUFFER, VboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*DataSize, DataArray, GL_STATIC_DRAW);
    return VboID;
}

GLuint CGCore::Loader::LoadToVBO(const GLuint Indices[], const GLuint ArraySize)
{
    // printf("Index Loader\n");
    GLuint VboID; 
    glGenBuffers(1,&VboID);
    VBOContainer.push_back(VboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*ArraySize, Indices, GL_STATIC_DRAW);
    return VboID;
}

void CGCore::Loader::StoreDataInAttrList(GLuint AttrNumber, GLuint AttrSize, const GLfloat Data[], GLuint DataSize)
{
    GLuint VboID; 
    glGenBuffers(1,&VboID);
    VBOContainer.push_back(VboID);
    glBindBuffer(GL_ARRAY_BUFFER, VboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*DataSize, Data, GL_STATIC_DRAW);
    glVertexAttribPointer(AttrNumber, AttrSize, GL_FLOAT, GL_FALSE, 0, (void*) 0); // write to VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind current VBO
}

void CGCore::Loader::UnbindVAO()
{
    glBindVertexArray(0); // Unbind any VAOs
}
