#pragma once

#include <Text.hpp>

namespace rwc
{

class FontFactory
{
public:
    FontFactory() = delete;

    static Text::Font create(const char* metadataPath);
};

} // namespace rwc

