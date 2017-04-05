#ifndef CG_SHADER_HPP
#define CG_SHADER_HPP

namespace CGCore
{
    class Shader
    {
        private:
            int ProgramID;
            int VertexShaderID;
            int FragmentShaderID;

            std::string readFile(const char *FileName);
        protected:
            virtual int LoadShader(const char* FileName, int ShaderType);

    };
}
    

#endif