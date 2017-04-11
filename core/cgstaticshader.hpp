#ifndef CG_STATICSHADER_HPP
#define CG_STATICSHADER_HPP

#include <vector>
#include <GL/glew.h>

namespace CGCore
{

    // static const char* VERTEX_FILENAME = "/Users/tanerselim/Dev/Quadtree_LOD/core/shaders/hello.vsh";
    // static const char* FRAGMENT_FILENAME = "/Users/tanerselim/Dev/Quadtree_LOD/core/shaders/hello.fsh";

    // Shaders with a texture
    static const char* VERTEX_FILENAME = "/Users/tanerselim/Dev/Quadtree_LOD/core/shaders/hello_tex.vsh";
    static const char* FRAGMENT_FILENAME = "/Users/tanerselim/Dev/Quadtree_LOD/core/shaders/hello_tex.fsh";
    //textureCoords
    class StaticShader : public CGCore::Shader
    {
        protected:
            virtual void BindAttributes() override;
        public:
            StaticShader();
            virtual ~StaticShader() {}
    };
}

#endif
