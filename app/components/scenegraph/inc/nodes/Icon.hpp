#pragma once

#include <nodes/Plane3D.hpp>

namespace rwc
{

class Icon : public Plane3D
{
public:
    Icon(
        const glm::mat4& viewProjectionMatrix
        , const char* iconPath
        , const glm::mat4& transformation = glm::mat4{1.0f});

    ~Icon() override;

    void setActive(bool active);
};

} // namespace rwc