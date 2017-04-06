#ifndef CG_TEXTURE_HPP
#define CG_TEXTURE_HPP

#include <GL/glew.h>

namespace CGCore
{
    // A representation of a texture image - currently png only
    class Texture
    {
        private:
            int Height;
            int Width;
            bool HasAlpha;
            GLubyte* TextureData = nullptr;
            
            Texture() {} // Can't be instatiated using default constructor'
            bool LoadPNG(
                    const char* name, int& outWidth, int& outHeight, bool& outHasAlpha, 
                    GLubyte** outData 
                ); // Load texture libpng 
            void LoadTexture(const char* FileName);
        public:
            Texture(const char* PNGFileName); // Textures for now must be PNG
            bool CheckHasAlpha() const { return HasAlpha; }
            int GetHeight() const { return Height; }
            int GetWidth() const { return Width; }
            GLubyte* GetTexture() const { return TextureData; }
    };
}
    

#endif