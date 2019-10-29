#pragma once

#include <string>

namespace rwc
{

/*!
 * @class ProgramGenerator
 *
 * @brief This is a class responsible for creating binary shaders for OpenGLSC
 *
 * @param[in] getAddress glfw function responsible for obtaining GPU expensions
 */
class ProgramGenerator {
 public:
    ProgramGenerator();

/*!
 * @brief generates binary with program object
 *
 * @param[in] fsPath path to fragment shader in text format
 *
 * @param[in] vsPath path to vertex shader in text format
 *
 * @param[in] binPath path to where the binary program object will be generated
 */
    void generate(const char* fsPath, const char* vsPath, const char* binPath);

 private:
    void generateBinary(const char* vsCode, const char* fsCode, const char* binaryName);
    std::string readShader(const char* filePath);
    void loadShader(const char* code, unsigned int type, unsigned int pipelineId);
};

} // namespace rwc

