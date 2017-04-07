#include "cgtexturedmodel.hpp"
#include "cgrawmodel.hpp"
#include "cgtexture.hpp"

CGCore::TexturedModel::TexturedModel(CGCore::RawModel* LpModel, CGCore::Texture* LpTexture)
{
    CurRawModel = LpModel;
    CurTexture = LpTexture;
}

CGCore::RawModel* CGCore::TexturedModel::GetModel() const 
{ 
    return CurRawModel; 
}

CGCore::Texture* CGCore::TexturedModel::GetTexture() const 
{ 
    return CurTexture; 
}