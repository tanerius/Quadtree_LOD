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
	// If something fails here stop
	bool HasFailed = false;
	GLint Result = GL_FALSE;
	int InfoLogLength;

    // Create the shaders

	// Vertex shader
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	char VertexSource[MAX_SHADER_LENGTH];
	HasFailed = !ReadFile (VertexShader, VertexSource, MAX_SHADER_LENGTH);
	if (HasFailed) {
		printf("Could not open vshader file: %s\n", VertexShader);
		exit(EXIT_FAILURE); 
	}
	// Read the Vertex Shader code from the file
    const GLchar* VertexSourcePointer = (const GLchar*) VertexSource;
    // Compile Vertex Shader
	printf("Compiling shader : %s\n", VertexShader);
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);
	glFinish();
    // Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
        HasFailed = true;
	}

	// Fragment shader
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	char FragmentSource[MAX_SHADER_LENGTH];
	HasFailed = !ReadFile (FramentShader, FragmentSource, MAX_SHADER_LENGTH);
	if (HasFailed) {
		printf("Could not open fshader file: %s\n", FramentShader);
		exit(EXIT_FAILURE); 
	}
	const GLchar* FragmentSourcePointer = (const GLchar*) FragmentSource;
    // Compile Fragment Shader
	printf("Compiling shader : %s\n", FramentShader);
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);
	glFinish();
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

	// Clean up
    glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	glFinish();

    if (HasFailed) exit(EXIT_FAILURE);
    return ProgramID;
}


bool CGCore::Shader::ReadFile ( const char* file_name, char* shader_str, int max_len) 
{
	shader_str[0] = '\0'; // reset string
	FILE* file = fopen (file_name , "r");
	if (!file) {
		printf ("ERROR: opening file for reading: %s\n", file_name);
		return false;
	}
	int current_len = 0;
	char line[2048];
	strcpy (line, ""); // remember to clean up before using for first time!
	while (!feof (file)) {
		if (NULL != fgets (line, 2048, file)) {
			current_len += strlen (line); // +1 for \n at end
			if (current_len >= max_len) {
				printf (
					"ERROR: shader length is longer than string buffer length %i\n",
					max_len
				);
			}
			strcat (shader_str, line);
		}
	}
	if (EOF == fclose (file)) { // probably unnecesssary validation
		printf ("ERROR: closing file from reading %s\n", file_name);
		return false;
	}
	return true;
}

