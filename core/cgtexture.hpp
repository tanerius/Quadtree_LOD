#ifndef CG_TEXTURE_HPP
#define CG_TEXTURE_HPP

#include <GL/glew.h>

namespace CGCore
{
    // A representation of a texture image - currently png only
    class Texture
    {
        private:
            GLuint TextureID;
            int Height;
            int Width;
            bool IsLoadedCorrectly;
            
            Texture() {} // Can't be instatiated using default constructor'
            void GenerateTexture(GLuint temp_width, GLuint temp_height, GLint format, GLubyte* image_data);
            bool LoadPNG(const char* name); // Load texture libpng 
            void LoadTexture(const char* FileName);
        public:
            Texture(const char* PNGFileName); // Textures for now must be PNG
            ~Texture();
            bool CheckIsLoaded() const { return IsLoadedCorrectly; }
            int GetHeight() const { return Height; }
            GLuint GetTextureID() const { return TextureID; }
            int GetWidth() const { return Width; }
    };
}
    

#endif
