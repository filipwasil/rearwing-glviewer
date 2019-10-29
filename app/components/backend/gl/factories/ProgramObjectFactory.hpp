#pragma once

#include <string>
#include <vector>

namespace rwc
{

/*!
 * @class ProgramObjectFactory
 *
 * @brief Loads an OpenGL Program Object
 *
 */
class ProgramObjectFactory
{
public:
    ProgramObjectFactory() = delete;

/*!
 * @brief Loads an OpenGL Program Object
 *
 * @param fsPath path to file containing fragment shader code
 *
 * @param vsPath path to the file containing fragment shader code
 *
 */
    static unsigned int load(const char* fsPath, const char* vsPath);

/*!
 * @brief Loads an OpenGL Program Object
 *
 * @param pathToBinary path to the file containing program object binary
 *
 */
    static unsigned int load(const char* pathToBinary);

/*!
 * @brief Loads an OpenGL Program Object
 *
 * @param getAddress callback function responsible for loading OpenGL extensions
 *
 * @param pathToBinary path to the file containing program object binary
 *
 */
    static unsigned int load(std::add_pointer_t<std::add_pointer_t<void(void)>(const char*)> getAddress, const char* pathToBinary);

private:
    static std::string readShader(const char* filePath);
    static void loadShader(const char* code, unsigned int type, unsigned int pipelineId);
    static std::string getErrorMessage(unsigned int pipelineId);
};

} // namespace rwc
