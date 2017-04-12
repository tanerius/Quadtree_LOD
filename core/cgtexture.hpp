#ifndef CG_TEXTURE_HPP
#define CG_TEXTURE_HPP

#include <GL/glew.h>

namespace CGCore
{
    class StaticShader;

    // A representation of a texture image - currently png only
    class Texture
    {
        private:
            GLuint TextureID;
            bool IsLoadedCorrectly;

            
            Texture() {} // Can't be instatiated using default constructor'
            void GenerateTexture(GLuint temp_width, GLuint temp_height, GLint format, GLubyte* image_data);
            bool LoadPNGFile(const char* name); // Load texture libpng 
            void LoadTextureFile(const char* FileName);
        public:
            Texture(const char* PNGFileName); // Textures for now must be PNG 
            ~Texture();
            
            void ApplyTexture(GLuint TextureSamplerHnd, int TextureUnit = 0);
            bool CheckIsLoaded() const { return IsLoadedCorrectly; }
            GLuint GetTextureID() const { return TextureID; }
            
    };
}
    

#endif
