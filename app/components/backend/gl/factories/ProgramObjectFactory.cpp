#include "ProgramObjectFactory.hpp"

#include <Config.hpp>
#include <Exception.hpp>

#include <glad/glad.h>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    static constexpr int VALID_NUMBER_OF_SUPPORTED_BINARY_FORMATS {1};
}

namespace rwc {

void ProgramObjectFactory::loadShader(const char* code, unsigned int type, unsigned int programObject)
{
    const GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &code, nullptr);
    glCompileShader(id);
    GLint status = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status) {
        glDeleteShader(id);
        throw Exception{"Shader failed to load", LOCATION};
    }

    glAttachShader(programObject, id);
}

std::string ProgramObjectFactory::readShader(const char* filePath)
{
    std::ifstream file(filePath, std::ios::in);
    if (!file.is_open() || !file.good()) {
        throw Exception{std::string("File ") + filePath + " not found", LOCATION};
    }
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

unsigned int ProgramObjectFactory::load(const char* fsPath, const char* vsPath)
{
    const auto fsCode = readShader(fsPath);
    const auto vsCode = readShader(vsPath);

    const GLuint id = glCreateProgram();

    loadShader(vsCode.c_str(), GL_VERTEX_SHADER, id);
    loadShader(fsCode.c_str(), GL_FRAGMENT_SHADER, id);

    GLint Success {0};

    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &Success);
    if (0 == Success) {
        throw Exception{getErrorMessage(id), LOCATION};
    }

    glValidateProgram(id);
    glGetProgramiv(id, GL_VALIDATE_STATUS, &Success);
    if (0 == Success) {
        throw Exception{getErrorMessage(id), LOCATION};
    }

    return id;
}

unsigned int ProgramObjectFactory::load(std::add_pointer_t<std::add_pointer_t<void(void)>(const char*)> getAddress, const char* pathToBinary)
{
    glGetProgramBinaryOES = reinterpret_cast<PFNGLGETPROGRAMBINARYOESPROC>(getAddress("glGetProgramBinaryOES"));
    if (nullptr == glGetProgramBinaryOES) {
        throw Exception{"OpenGL ES extension glGetProgramBinaryOES failed to initialize", LOCATION};
    }
    glProgramBinaryOES = reinterpret_cast<PFNGLPROGRAMBINARYOESPROC>(getAddress("glProgramBinaryOES"));
    if (nullptr == glProgramBinaryOES) {
        throw Exception{"OpenGL ES extension glProgramBinaryOES failed to initialize", LOCATION};
    }
    return load(pathToBinary);
}

unsigned int ProgramObjectFactory::load(const char* pathToBinary)
{
    GLint formats {0};
    glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS_OES, &formats);
    if (VALID_NUMBER_OF_SUPPORTED_BINARY_FORMATS != formats) {
        throw Exception(std::string("Number of supported binary formats invalid: ") + std::to_string(formats), LOCATION);
    }

    std::ifstream file(pathToBinary, std::ios::binary | std::ios::ate);
    if (!file.is_open() || !file.good()) {
        throw Exception(std::string("File not found: ") + pathToBinary, LOCATION);
    }

    const auto end = file.tellg();
    file.seekg(0, std::ios::beg);

    const auto size = std::size_t(end - file.tellg());
    std::vector<char> buffer(size);

    if (!file.read(buffer.data(), std::streamsize(buffer.size()))) {
        throw Exception(std::string("File reading failed: ") + pathToBinary, LOCATION);
    }

    GLint binaryFormat {};
    glGetIntegerv(GL_PROGRAM_BINARY_FORMATS_OES, &binaryFormat);

    GLuint progId = glCreateProgram();
    glProgramBinaryOES(progId, static_cast<GLenum>(binaryFormat), buffer.data(), static_cast<GLint>(size));

    GLint success {0};
    glGetProgramiv(progId, GL_LINK_STATUS, &success);
    if (!success) {
        throw Exception(std::string("Failed to link binary shader: ") + pathToBinary, LOCATION);
    }

    return progId;
}

std::string ProgramObjectFactory::getErrorMessage(GLuint pipelineId)
{
    GLint maxInfoLength {0};
    glGetProgramiv(pipelineId, GL_INFO_LOG_LENGTH, &maxInfoLength);
    if ( 0 >= maxInfoLength) {
        throw Exception("Error message lenght returned negative value ", LOCATION);
    }

    std::vector<char> msg ( static_cast<std::vector<char>::size_type>(maxInfoLength), '\0' );
    glGetProgramInfoLog(pipelineId, static_cast<GLsizei>(msg.size()), nullptr, msg.data());
    return std::string(msg.begin(), msg.end());
}

} // namespace rwc