#include "cgdisplay.hpp"
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Definitions for the callbacks
class CGCallbacks
{
    public:
    static void ErrorCallback(int error, const char* description) 
    {
        fputs(description, stderr);
    }

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
};

bool CGCore::DisplayManager::CloseRequested()
{
    return glfwWindowShouldClose(GLFWWindowPtr);
}

void CGCore::DisplayManager::CreateDisplay()
{
    // Creating a display
    assert(GLFWWindowPtr == 0);
    // Initialize GLFW, and if it fails to initialize for any reason, print it out to STDERR.
    // Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		exit(EXIT_FAILURE);
	}

#ifdef APPLE
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Try 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // try 1
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    
    // Create a window to put our stuff in.
    GLFWWindowPtr = glfwCreateWindow(DisplayWidth, DisplayHeight, "Quadtree LOD", NULL, NULL);

    if( GLFWWindowPtr == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(GLFWWindowPtr);

    glfwSetKeyCallback(GLFWWindowPtr, CGCallbacks::KeyCallback); // key capture
    glfwSetErrorCallback(CGCallbacks::ErrorCallback);

    // Initialize GLEW
	glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		exit(EXIT_FAILURE);
	}
    // Ensure we can capture the escape key being pressed below
	glfwSetInputMode(GLFWWindowPtr, GLFW_STICKY_KEYS, GL_TRUE);

    
}

void CGCore::DisplayManager::DestroyDisplay()
{
    // Destroy the display 
    glfwDestroyWindow(GLFWWindowPtr);
    glfwTerminate();
}

void CGCore::DisplayManager::GetInfo()
{
    printf("GL Information:\n");
    printf("Supported GL version: %s \n",glGetString(GL_VERSION));
    printf("Supported shading lang: %s \n",glGetString (GL_SHADING_LANGUAGE_VERSION));
    printf("Current GL vendor: %s \n",glGetString(GL_VENDOR));
    printf("Current GL renderer: %s \n",glGetString(GL_RENDERER));
}

void CGCore::DisplayManager::UpdateDisplay()
{
    // Swap the buffers so that what we drew will appear on the screen.
    glfwSwapBuffers(GLFWWindowPtr);
    glfwPollEvents();
}

void CGCore::DisplayManager::WriteDisplay(const char* Msg)
{
    printf("Log: %s", Msg);
}
