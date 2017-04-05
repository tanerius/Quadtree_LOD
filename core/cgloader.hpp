#ifndef CG_LOADER_HPP
#define CG_LOADER_HPP
#include <vector>
#include <GL/glew.h>

class RawModel;


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
            // Properties
            std::vector<GLuint> VAOContainer;
            std::vector<GLuint> VBOContainer;
            // Members
            GLuint CreateVAO(); // returns a new VaoID
            void StoreDataInAttrList(GLuint AttrNumber, GLfloat Data[], GLuint DataSize);
            void UnbindVAO();
        public:
            void CleanUp(); // TODO: implement this to clean up vaos and vbos
            RawModel LoadToVAO(GLfloat Positions[], GLuint ArraySize);
            
    };

} 

#endif