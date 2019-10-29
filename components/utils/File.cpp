#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "inc/File.hpp"

namespace rwc
{

std::vector<char> readBinary(const char* filePath) {
  std::ifstream input(std::string("../../assets/") + std::string(filePath), std::ios::binary );
  return {(std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>())};
}

} // namespace rwc
