#ifndef CG_SHADER_HPP
#define CG_SHADER_HPP

#include <vector>
#include <GL/glew.h>

namespace CGCore
{
    // An abstract class representing a shader - can't be instantiated on its own
    class Shader
    {
        private:
            GLuint ProgramID;
            GLuint VertexShaderID;
            GLuint FragmentShaderID;
            std::vector <char*> VertShaderError;

            const char* ReadFile(const char *FileName);
        protected:
            virtual void BindAttributes() = 0; // PURE VIRTUAL !!!
            virtual GLuint LoadShader(const char* FileName, GLenum ShaderType);
        public:
            void BindAttribute(int Attrib, const GLchar* VarName);
            void CleanUp();
            Shader(const char* VertexFile, const char* FragmentFile);
            void StartProgram();
            void StopProgram();

    };
}
    

#endif