#include "cgdisplay.hpp"
#include "cgrawmodel.hpp"
#include "cgloader.hpp"

int main()
{
    CGCore::DisplayManager* Display = new CGCore::DisplayManager();
    Display->WriteDisplay("Hello from display manager! \n");
    Display->GetInfo();



    Display->CreateDisplay();
    while(!Display->CloseRequested())
    {
        // Write game loop here
        Display->UpdateDisplay();
    }
    Display->DestroyDisplay();
    delete Display;
    
    return 0;
}