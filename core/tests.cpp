#include "cgdisplay.hpp"
#include "cgrawmodel.hpp"
#include "cgshader.hpp"
#include "cgstaticshader.hpp"
#include "cgloader.hpp"
#include "cgrenderer.hpp"
#include "cgtexture.hpp"
//#include "cgtexturedmodel.hpp"

int main()
{
    CGCore::DisplayManager* Display = new CGCore::DisplayManager();
    Display->WriteDisplay("Hello from display manager! \n");
    

    Display->CreateDisplay();

    CGCore::Loader* LoaderObj = new CGCore::Loader();
    CGCore::Renderer* RendererObj = new CGCore::Renderer();
    Display->GetInfo();
    CGCore::StaticShader* StaticShaderObj = new CGCore::StaticShader();

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

    CGCore::RawModel* ModelObj = LoaderObj->LoadToVAO(PossibleVertices, 12, Indices, 6);
    CGCore::Texture* TextureObj = new CGCore::Texture("../res/img_noalpha.png");
    //CGCore::TexturedModel* TMObj = new CGCore::TexturedModel(ModelObj, TextureObj);

    while(!Display->CloseRequested())
    {
        // Write game loop here
        RendererObj->Prepare();
        StaticShaderObj->StartProgram();
        RendererObj->Render(ModelObj);
        StaticShaderObj->StopProgram();
        Display->UpdateDisplay();
    }

    StaticShaderObj->CleanUp();
    LoaderObj->CleanUp();
    Display->DestroyDisplay();
    delete ModelObj;
    delete TextureObj;
    delete StaticShaderObj;
    delete Display;
    delete LoaderObj;

    
    return 0;
}