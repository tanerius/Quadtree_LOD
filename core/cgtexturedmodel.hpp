#ifndef CG_TEXTURED_MODEL_HPP
#define CG_TEXTURED_MODEL_HPP

#include <GL/glew.h>

namespace CGCore
{
    class RawModel;
    class Texture;

    // This class stores a model in memory
    class TexturedModel
    {
        private:
            CGCore::RawModel* CurRawModel = nullptr;
            CGCore::Texture* CurTexture = nullptr;
        public:
            TexturedModel(CGCore::RawModel* LpModel, CGCore::Texture* LpTexture);
            CGCore::RawModel* GetModel() const;
            CGCore::Texture* GetTexture() const; 
    };

} 

#endif