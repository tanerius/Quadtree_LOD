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
    assert(GLFWWindowPtr == nullptr);
    // Initialize GLFW, and if it fails to initialize for any reason, print it out to STDERR.
    if (!glfwInit()) 
    {
        WriteDisplay("Failed initialize GLFW.\n");
        exit(EXIT_FAILURE);
    }
    glfwSetErrorCallback(CGCallbacks::ErrorCallback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // Indicate we only want the newest core profile, rather than using backwards compatible and deprecated features.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Make the window non resizeable.
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    // Create a window to put our stuff in.
    GLFWWindowPtr = glfwCreateWindow(DisplayWidth, DisplayHeight, "OpenGL", NULL, NULL);

    // If the window fails to be created, clean up.
    if(!GLFWWindowPtr) {
        WriteDisplay("Failed to create GLFW window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(GLFWWindowPtr);
    glfwSetKeyCallback(GLFWWindowPtr, CGCallbacks::KeyCallback); // key capture

    // Init glew stuff
    glewExperimental = GL_TRUE;
    glewInit();
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
}

void CGCore::DisplayManager::UpdateDisplay()
{
    // Swap the buffers so that what we drew will appear on the screen.
    glfwSwapBuffers(GLFWWindowPtr);
    glfwPollEvents();
}

void CGCore::DisplayManager::WriteDisplay(const char* Msg)
{
    printf("Log (%lu b): %s", sizeof(GLfloat), Msg);
}