#include "cgtexturedmodel.hpp"
#include "cgtexture.hpp"
#include "cgrawmodel.hpp"

CGCore::TexturedModel::TexturedModel(CGCore::RawModel* LpModel, CGCore::Texture* LpTexture) 
{
    CurRawModel = LpModel;
    CurTexture = LpTexture;
}