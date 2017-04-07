#ifndef CG_LOADER_HPP
#define CG_LOADER_HPP
#include <vector>
#include <GL/glew.h>
class RawModel;
class Texture;
namespace CGCore
{
    
    struct VertexSimple
    {
        GLfloat x, y, z;        //Vertex
        GLfloat padding;        // to keep this struct 16bytes
    };

    
    // This class loads 3d models into memory by storing positional data of model in a VAO (vertex array object)
    class Loader
    {
        private:
            // containers to keep things clean
            std::vector<GLuint> VAOContainer;
            std::vector<GLuint> VBOContainer;
            std::vector<Texture*> TextureContainer;
            // Members
            void BindIndicesBufferVBO(GLuint Indices[], GLuint ArraySize);
            GLuint CreateVAO(); // returns a new VaoID
            void StoreDataInAttrList(GLuint AttrNumber, GLfloat Data[], GLuint DataSize);
            void UnbindVAO();
        public:
            void CleanUp(); 
            Texture* LoadTexture(const char* FileName);
            RawModel* LoadToVAO(GLfloat Positions[], GLuint PosArrySize, GLuint Indices[], GLuint IndArrySize);
    };

} 

#endif