#pragma once

#include <nodes/Node3D.hpp>

namespace rwc
{

class Plane3D : public Node3D
{
public:
    Plane3D(
        const glm::mat4& viewProjectionMatrix
        , const glm::mat4& transformation
        , const char* vertexShaderPath
        , const char* fragmentShaderPath
        , const char* texturePath);

  Plane3D(
    const glm::mat4& viewProjectionMatrix
    , const glm::mat4& transformation
    , const char* binaryShaderPath
    , const char* texturePath);

    ~Plane3D() override;
};

} // namespace rwc