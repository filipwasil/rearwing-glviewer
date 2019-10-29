#pragma once

#include "ProgramGenerator.hpp"
#include <memory>

namespace rwc
{

/*!
 * @class OffscreenContext
 *
 * @brief Creates an offscreen context to generate binary shaders
 */
class OffscreenContext final {
public:
    OffscreenContext();
    ~OffscreenContext();

/*!
 * @brief Generates binary with program object
 *
 * @param[in] fragmentShaderPath file path from which read the fragment shader code
 *
 * @param[in] vertexShaderPath file path from which read the vertex shader code
 *
 * @param[in] programBinaryPath file path to which save the binary shader
 *
 */
    void generateProgramBinary(
        const std::string& fragmentShaderPath
        , const std::string& vertexShaderPath
        , const std::string& programBinaryPath
        , const std::string& prefixPath
        , const std::string& outputPath);

private:
    std::unique_ptr<ProgramGenerator> mGenerator;
};

} // namespace rwc
