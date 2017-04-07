#ifndef CG_RAW_MODEL_HPP
#define CG_RAW_MODEL_HPP
#include <GL/glew.h>

namespace CGCore
{
    class CGCore::RawModel;
    class CGCore::Texture;

    // This class stores a model in memory
    class TexturedModel
    {
        private:
            CGCore::RawModel* CurRawModel = nullptr;
            CGCore::Texture* CurTexture = nullptr;
        public:
            TexturedModel(CGCore::RawModel* LpModel, CGCore::Texture* LpTexture);
            CGCore::RawModel* GetModel() const { return CurRawModel; }
            CGCore::Texture* GetTexture() const { return CurTexture; }
    };

} 

#endif