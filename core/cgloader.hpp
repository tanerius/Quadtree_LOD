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
            void BindIndicesBufferVBO(const GLuint Indices[], GLuint ArraySize);
            void StoreDataInAttrList(GLuint AttrNumber, GLuint AttrSize, const GLfloat Data[], GLuint DataSize);
            void UnbindVAO();
        public:
            void CleanUp(); 
            void CreateBindVAO(); // returcreates a new VAO and stores it in a contanier
            RawModel* LoadToVAO
                (
                    const GLfloat Positions[], GLuint PosArrySize, 
                    const GLuint Indices[], GLuint IndArrySize,
                    const GLfloat TexCoords[], GLuint TCArrySize 
                );
            GLuint LoadToVBO(const GLfloat DataArray[], const GLuint DataSize);
            GLuint LoadToVBO(const GLuint Indices[], const GLuint ArraySize);
    };

} 

#endif
