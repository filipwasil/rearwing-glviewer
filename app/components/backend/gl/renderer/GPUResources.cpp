#include "GPUResources.hpp"
#include <ConfigGL.hpp>

namespace rwc
{

GPUResources::~GPUResources()
{
    for (const auto& buffer : buffers)
    {
        glDeleteBuffers(1, &buffer);
    }

    for (const auto& program : programs)
    {
        glDeleteProgram(program);
    }

    for (const auto& vertexArray : vertexArrays)
    {
        glDeleteVertexArrays(1, &vertexArray);
    }

    for (const auto& texture : textures)
    {
        glDeleteTextures(1, &texture);
    }
}

} // namespace rwc