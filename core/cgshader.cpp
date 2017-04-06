#include "cgshader.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void CGCore::Shader::BindAttribute(int Attrib, const GLchar* VarName)
{
    glBindAttribLocation(ProgramID, Attrib, VarName);
}

void CGCore::Shader::CleanUp()
{
    // Do some cleaning up of mem
    // Stop program
    StopProgram();
    // detach and delete shaders
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    glDeleteProgram(ProgramID);
}

CGCore::Shader::Shader(const char* VertexFile, const char* FragmentFile)
{
    VertexShaderID = LoadShader(VertexFile, GL_VERTEX_SHADER);
    FragmentShaderID = LoadShader(FragmentFile, GL_FRAGMENT_SHADER);
    // Linking a program
    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    glValidateProgram(ProgramID);

    // Check that the program compiled and can work
    GLint Result = GL_FALSE;
    int logLength;
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &logLength);
    char* err = nullptr;
    if(logLength > 1)
    {
        err = (char*)malloc(sizeof(char)*logLength+1);
        glGetProgramInfoLog(ProgramID, logLength, NULL, err);
        std::cout << err << std::endl;
        free(err);
        err = nullptr;
    }
     
    // BindAttributes(); // this is pure virtual don't call it from here
    if( Result == GL_FALSE )
    {
        //std::cout << VertShaderError[0] << std::endl;
        std::cout << "Cannot link shader program!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void CGCore::Shader::StartProgram()
{
    // Start a shader program on the current rendering state
    glUseProgram(ProgramID);
}

void CGCore::Shader::StopProgram()
{
    // Sto current shader program
    glUseProgram(0);
}

GLuint CGCore::Shader::LoadShader(const char* FileName, GLenum ShaderType)
{
    // Read the shader
    const char* ShaderCode = ReadFile(FileName);
    GLuint ShaderHandle = glCreateShader(ShaderType);

    GLint Result = GL_FALSE;
    int LogLength;

    // Compile the shader
    glShaderSource(ShaderHandle, 1, &ShaderCode, NULL);
    glCompileShader(ShaderHandle);
    // Check shader
    glGetShaderiv(ShaderHandle, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(ShaderHandle, GL_INFO_LOG_LENGTH, &LogLength);

    char* err = nullptr;
    if(LogLength > 1)
    {
        err = (char*)malloc(sizeof(char)*LogLength+1);
        glGetShaderInfoLog(ShaderHandle, LogLength, NULL, err);
        if(ShaderType == GL_VERTEX_SHADER)
        {
            std::cout << "Vertex shader error:" << std::endl;
        }
        else
        {
            std::cout << "Fragment shader error:" << std::endl;
        }
        std::cout << err << std::endl;
        free(err);
        err = nullptr;
    }

    if( Result == GL_FALSE )
    {
        //std::cout << VertShaderError[0] << std::endl;
        std::cout << "Cannot compile shader!" << std::endl;
        exit(EXIT_FAILURE);
        return 0;
    }
    
    return ShaderHandle;
}

const char* CGCore::Shader::ReadFile(const char *FileName) {
    std::string content;
    std::ifstream fileStream(FileName, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << FileName << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();

    return content.c_str();
}