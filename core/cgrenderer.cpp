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

void CGCore::Renderer::Render()
{
   // Main rendering code
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
