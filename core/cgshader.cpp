#include "cgshader.hpp"
#include <string>
#include <iostream>
#include <fstream>


int CGCore::Shader::LoadShader(const char* FileName, int ShaderType)
{
    return 0;
}

std::string CGCore::Shader::ReadFile(const char *FileName) {
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
    return content;
}