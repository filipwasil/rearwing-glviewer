#pragma once

#include <string>

namespace rwc
{

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;
    virtual void onMessage(const std::string &msg);
};

} // namespace rwc
