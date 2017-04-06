#ifndef CG_SHADER_HPP
#define CG_SHADER_HPP

#include <vector>
#include <GL/glew.h>

namespace CGCore
{
    class Shader
    {
        private:
            GLuint ProgramID;
            GLuint VertexShaderID;
            GLuint FragmentShaderID;
            std::vector VertShaderError;

            const char* ReadFile(const char *FileName);
        protected:
            virtual void BindAttributes();
            virtual GLuint LoadShader(const char* FileName, GLenum ShaderType);
        public:
            Shader(const char* VertexFile, const char* FragmentFile);

    };
}
    

#endif