#include "cgshader.hpp"
#include "cgstaticshader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

CGCore::StaticShader::StaticShader() : Shader(CGCore::VERTEX_FILENAME, CGCore::FRAGMENT_FILENAME)
{
    BindAttributes();
}

void CGCore::StaticShader::BindAttributes()
{
    BindAttribute(0, "position");
}