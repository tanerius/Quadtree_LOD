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
            const char* ReadFile(const char *FileName);
        protected:
            virtual void BindAttributes() = 0; // PURE VIRTUAL !!!
            virtual GLuint LoadShaders(const char* VertexShader, const char* FramentShader);
        public:
            void BindAttribute(int Attrib, const GLchar* VarName);
            void CleanUp();
            GLuint GetProgramID() const { return ProgramID; }
            Shader(const char* VertexFile, const char* FragmentFile);
            void StartProgram();
            void StopProgram();

    };
}
    

#endif