#include "inc/Strings.hpp"

namespace rwc
{

std::string getFilePathOnly(const char* path) {
    if (std::string(path).find("/") != std::string::npos) {
        return std::string(path).substr(0, std::string(path).find_last_of("/"));
    }
    return "./";
}

std::string getFileNameOnly(const char* path) {
    if (std::string(path).find("/") != std::string::npos) {
        return std::string(path).substr(std::string(path).find_last_of("/") + 1, std::string(path).size());
    }
    return std::string(path);
}

} // namespace rwc