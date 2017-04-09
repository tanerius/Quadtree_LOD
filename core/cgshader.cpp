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
    glDeleteProgram(ProgramID);
}

CGCore::Shader::Shader(const char* VertexFile, const char* FragmentFile)
{
    LoadShaders(VertexFile, FragmentFile);
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


GLuint CGCore::Shader::LoadShaders(const char* VertexShader, const char* FramentShader)
{
    // Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
    const char* VertexSourcePointer = ReadFile(VertexShader);
    const char* FragmentSourcePointer = ReadFile(FramentShader);

    GLint Result = GL_FALSE;
	int InfoLogLength;
    bool HasFailed = false;

    // Compile Vertex Shader
	printf("Compiling shader : %s\n", VertexShader);
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);
    // Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
        HasFailed = true;
	}

    // Compile Fragment Shader
	printf("Compiling shader : %s\n", FramentShader);
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
        HasFailed = true;
	}

    // Link the program
	printf("Linking program\n");
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

    // Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
        HasFailed = true;
	}

    glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

    if (HasFailed) exit(EXIT_FAILURE);
    return ProgramID;
}


const char* CGCore::Shader::ReadFile(const char *FileName) {
    // Read the Vertex Shader code from the file
	std::string ShaderCode;
	std::ifstream ShaderStream(FileName, std::ios::in);
	if(ShaderStream.is_open()){
		std::string Line = "";
		while(getline(ShaderStream, Line))
			ShaderCode += "\n" + Line;
		ShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? \n", FileName);
		getchar();
		return "";
	}

    printf("Shader dump:\n%s\n\n",ShaderCode.c_str());
    return ShaderCode.c_str();
}