#include "cgtexturedmodel.hpp"
#include "cgrenderer.hpp"
#include "cgrawmodel.hpp"
#include "cgtexture.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void CGCore::Renderer::Prepare()
{
    // Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
}

void CGCore::Renderer::Render(CGCore::TexturedModel* TexturedModelObj)
{
    CGCore::RawModel* Model = TexturedModelObj->GetModel();
    glBindVertexArray(Model->GetVaoID());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glActiveTexture(GL_TEXTURE0);
    glDrawElements(	GL_TRIANGLES, Model->GetVertexCount(), GL_UNSIGNED_INT, (void*) 0);
    glBindTexture(GL_TEXTURE_2D, TexturedModelObj->GetTexture()->GetTextureID());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void CGCore::Renderer::SetStates()
{
    // Dark blue background to start off with 
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    // Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
}