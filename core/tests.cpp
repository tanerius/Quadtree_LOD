#include "cgdisplay.hpp"
#include "cgrawmodel.hpp"
#include "cgloader.hpp"
#include "cgrenderer.hpp"


int main()
{
    CGCore::DisplayManager* Display = new CGCore::DisplayManager();
    Display->WriteDisplay("Hello from display manager! \n");
    Display->GetInfo();

    Display->CreateDisplay();

    CGCore::Loader* LoaderObj = new CGCore::Loader();
    CGCore::Renderer* RendererObj = new CGCore::Renderer();

    GLfloat PossibleVertices[] = {
        // Left bottom triangle
        -0.5f,  0.5f, 0.0f, // v0
        -0.5f, -0.5f, 0.0f, // v1
         0.5f, -0.5f, 0.0f, // v2
         0.5f,  0.5f, 0.0f  // v3
    };

    GLuint Indices[] = {
        0, 1, 3,
        3, 1, 2
    };

    CGCore::RawModel ModelObj = LoaderObj->LoadToVAO(PossibleVertices, 12, Indices, 6);

    while(!Display->CloseRequested())
    {
        // Write game loop here
        RendererObj->Prepare();
        RendererObj->Render(ModelObj);
        Display->UpdateDisplay();
    }

    LoaderObj->CleanUp();
    Display->DestroyDisplay();
    delete Display;
    
    return 0;
}