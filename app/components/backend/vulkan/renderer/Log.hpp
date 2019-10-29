#pragma once

#include <string>

#define ENABLE_DEBUG_LAYERS

namespace rwc
{

void logC(const std::string& msg, unsigned int res);
void logF(const std::string& msg);
void logD(const std::string& msg);
void logImageUsageFlags(unsigned int flags);

} // namespace rwe
