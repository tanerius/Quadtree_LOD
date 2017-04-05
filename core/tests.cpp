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

    GLfloat TriVertices[] = {
        // Left bottom triangle
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         // Right top triangle
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    CGCore::RawModel ModelObj = LoaderObj->LoadToVAO(TriVertices, 18);

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