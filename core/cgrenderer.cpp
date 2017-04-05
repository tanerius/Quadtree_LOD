#include "cgrawmodel.hpp"
#include "cgrenderer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void CGCore::Renderer::Prepare()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void CGCore::Renderer::Render(RawModel Model)
{
    glBindVertexArray(Model.GetVaoID());
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, Model.GetVertexCount());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}