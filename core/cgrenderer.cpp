#include "cgrenderer.hpp"
#include "cgtexturedmodel.hpp"
#include "cgrawmodel.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void CGCore::Renderer::Prepare()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // red background
    glClear(GL_COLOR_BUFFER_BIT);
}

void CGCore::Renderer::Render(CGCore::TexturedModel* Model)
{
    CGCore::RawModel* RawModelObj = Model->GetModel();
    glBindVertexArray(RawModelObj->GetVaoID());
    glEnableVertexAttribArray(0);
    // glDrawArrays(GL_TRIANGLES, 0, Model.GetVertexCount()); // Use this to draw directly given vertices
    // Draw based on positional instructions from the VBO index buffer
    glDrawElements(	GL_TRIANGLES, RawModelObj->GetVertexCount(), GL_UNSIGNED_INT, (void*) 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}