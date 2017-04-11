#ifndef CG_DISPLAY_HPP
#define CG_DISPLAY_HPP

#include <cstdio>

class GLFWwindow;

namespace CGCore 
{

    class DisplayManager
    {
        private:
            const int DisplayWidth = 1280;
            const int DisplayHeight = 720;
            // const int MaxFps = 120;

            GLFWwindow* GLFWWindowPtr = 0; // will hold our window pointer

        public:
            bool CloseRequested();
            void CreateDisplay();
            void DestroyDisplay();
            void GetInfo();
            void WriteDisplay(const char* Msg);
            void UpdateDisplay();
    };

}

#endif
