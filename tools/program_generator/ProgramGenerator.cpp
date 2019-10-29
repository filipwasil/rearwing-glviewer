#include "ProgramGenerator.hpp"
#include "Exception.hpp"

#include "ConfigGL.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <array>

namespace rwc
{

ProgramGenerator::ProgramGenerator() = default;

void ProgramGenerator::generate( const char* fsPath, const char* vsPath, const char* binPath)
{
    const auto fsCode = readShader(fsPath);
    const auto vsCode = readShader(vsPath);
    generateBinary(vsCode.c_str(), fsCode.c_str(), binPath);
}

void ProgramGenerator::loadShader(const char* code, unsigned int type, unsigned int pipelineId)
{
    GLuint id = glCreateShader(type);

    glShaderSource(id, 1, &code, nullptr);

    glCompileShader(id);

    GLint status = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status) {
        // Extract error
        GLint infoLogLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
        constexpr GLuint bufferLength = 1024;
        GLchar buffer[bufferLength];
        glGetShaderInfoLog(id, bufferLength, nullptr, buffer);
        std::cout << buffer << std::endl;
        glDeleteShader(id);
        throw ProgramGeneratorException{"Shader failed to load"};
    }

    glAttachShader(pipelineId, id);
}

std::string ProgramGenerator::readShader(const char* filePath) {
    std::ifstream file(filePath, std::ios::in);

    if (!file.is_open() || !file.good())
    {
        throw ProgramGeneratorException{"Shader file not found"};
    }
    else
    {
        std::cout << "Loading shader: " << filePath << "\n";
    }
    std::string data;
    std::string line;
    while (std::getline(file, line)) {
        data += line + "\n";
    }

    return data;
}

void ProgramGenerator::generateBinary(
    const char* vertexShaderCode
    , const char* fragmentShaderCode
    , const char* binaryName)
{
    GLuint id = glCreateProgram();

    loadShader(vertexShaderCode, GL_VERTEX_SHADER, id);
    loadShader(fragmentShaderCode, GL_FRAGMENT_SHADER, id);

    GLint success {0};
    std::array<char, 256> msg { '\0' };

    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, msg.size(), nullptr, msg.data()); // obtain error message
        throw ProgramGeneratorException{msg.data()};
    }

    glValidateProgram(id);
    glGetProgramiv(id, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, msg.size(), nullptr, msg.data()); // obtain error message
        throw ProgramGeneratorException{msg.data()};
    }

    glUseProgram(id);

    GLint format {0};
    glGetIntegerv(GL_PROGRAM_BINARY_FORMATS_OES, &format);

    int len;
    glGetProgramiv(id, GL_PROGRAM_BINARY_LENGTH_OES, &len);

    char* buffer = new char[len];
    glGetProgramBinaryOES(id, len, &len, (GLenum*)buffer, buffer);

    // save to file
    FILE* fp = fopen(binaryName, "w");
    if (nullptr == fp) {
        throw ProgramGeneratorException{"Could not write to file: " + std::string{binaryName}};
    }
    fwrite(buffer, 1, len, fp);
    fclose(fp);

    delete[] buffer;

    glDeleteProgram(id);
}

} // namespace rwc
