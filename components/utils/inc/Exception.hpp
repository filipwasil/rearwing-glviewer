#pragma once

#include <stdexcept>
#include <string>


#ifdef __linux__
constexpr const char* RWC_OS_SEPRATOR = "/";
constexpr const char* RWC_OS_CURRENTDIR = "./";
constexpr const char* RWC_OS_TEXTURE_SAMPLE_FACTOR = "vec2(1.0, 1.0)";
#elif _WIN32
constexpr const char* RWC_OS_SEPRATOR = "\\";
constexpr const char* RWC_OS_CURRENTDIR = "./";
constexpr const char* RWC_OS_TEXTURE_SAMPLE_FACTOR = "vec2(1.0, -1.0)";
#elif __APPLE__
constexpr const char* RWC_OS_SEPRATOR = "/";
constexpr const char* RWC_OS_CURRENTDIR = "./";
constexpr const char* RWC_OS_TEXTURE_SAMPLE_FACTOR = "vec2(1.0, -1.0)";
#endif

#define LOCATION \
      (std::string(__FILE__).find(RWC_OS_SEPRATOR) == std::string::npos ? std::string(__FILE__) : \
      std::string(__FILE__).substr(std::string(__FILE__).find_last_of(                            \
          RWC_OS_SEPRATOR) + 1, std::string(__FILE__).size()))

namespace rwc
{

class Exception : public std::runtime_error
{
 public:
    Exception(const std::string& desc, const std::string& prefix)
       : std::runtime_error(desc)
       , mPrefix(prefix)
    {
       // Empty
    }

    std::string getWhat() const
    {
       return mPrefix + "::" + std::string{what()};
    }

 protected:
  std::string mPrefix;
};

} /* namespace rwc */

