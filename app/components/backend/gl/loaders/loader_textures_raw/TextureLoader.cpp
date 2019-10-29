#include "TextureLoader.hpp"

#include "ConfigGL.hpp"
#include <Exception.hpp>
#include "stb_image.h"

#include <sstream>
#include <string>
#include <vector>

#include <Logger.hpp>

namespace rwc
{

unsigned int TextureLoader::load(const char* filePath)
{
  std::string path(filePath);

  auto split = [](const std::string& s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
      elems.push_back(item);
    }
    return elems;
  };

  if (path.empty()) {
    return loadEmpty(512, 512, GL_RGBA, GL_RGBA);
  }

  const size_t posColor = path.find(".color");
  if (posColor != std::string::npos) {
    std::vector<std::string> tokens = split(filePath, '_');
    if (tokens.size() < 3) {
      throw Exception{"Wrong format. Only uncompressed GL_RGBA and GL_RGB  textures are available", LOCATION};
    }
    return loadColor(512, 512, atoi(tokens[0].c_str()), atoi(tokens[1].c_str()), atoi(tokens[2].c_str()), GL_RGBA, GL_RGBA);
  }

  const size_t posCheckboard = path.find(".chessboard");
  if (posCheckboard != std::string::npos) {
    std::vector<std::string> tokens = split(filePath, '_');
    if (tokens.size() < 3) {
      throw Exception{"Could not found color parameters in requested path", LOCATION};
    }
    return loadChessboard(512, 512, atoi(tokens[0].c_str()), atoi(tokens[1].c_str()), atoi(tokens[2].c_str()), GL_RGBA, GL_RGBA);
  }

  return loadFromFile(filePath, GL_RGBA, GL_RGBA);
}

unsigned int TextureLoader::loadEmpty(GLsizei width, GLsizei height, GLenum format, GLint internalFormat)
{
  GLuint name {0};
  glGenTextures(1, &name);
  glBindTexture(GL_TEXTURE_2D, name);
  glTexImage2D(
    GL_TEXTURE_2D
    , 0 // mipmaps
    , internalFormat
    , width
    , height
    , 0 // border
    , format
    , GL_UNSIGNED_BYTE
    , nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return name;
}

unsigned int TextureLoader::loadChessboard(
  GLsizei width
  , GLsizei height
  , GLubyte red
  , GLubyte green
  , GLubyte blue
  , GLenum format
  , GLint internalFormat)
{
  if (GL_RGBA != format && GL_RGB != format) {
    throw Exception{
      "Unhandled format",
      LOCATION
    };
  }
  const GLint bytesPerPixel = GL_RGBA == format ? 4 : 3;

  const GLint size = bytesPerPixel * width * height;
  std::vector<GLubyte> content(static_cast<size_t>(size), 0);

  GLint i = 0;
  GLint r = 0;
  GLint g = 0;
  GLint b = 0;

  for (i = 0; i < size; i += bytesPerPixel)
  {
    if (0 == i % ((width * bytesPerPixel) * 8)) {
      r ^= red;
      g ^= green;
      b ^= blue;
    }
    if (0 == i % (bytesPerPixel * 8)) {
      r ^= red;
      g ^= green;
      b ^= blue;
    }
    size_t idx = static_cast<size_t>(i);
    content[idx] = r;
    content[idx + 1] = g;
    content[idx + 2] = b;
    content[idx + 3] = 255;
  }

  GLuint name {0};
  glGenTextures(1, &name);
  glBindTexture(GL_TEXTURE_2D, name);
  glTexImage2D(
    GL_TEXTURE_2D
    , 0 // mipmaps
    , internalFormat
    , width
    , height
    , 0 // border
    , format
    , GL_UNSIGNED_BYTE
    , content.data());

  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return name;
}

unsigned int TextureLoader::loadColor(GLsizei width, GLsizei height, GLubyte red, GLubyte green, GLubyte blue, GLenum format, GLint internalFormat)
{
  if (GL_RGBA != format && GL_RGB != format) {
    throw Exception{"Wrong format. Only uncompressed GL_RGBA and GL_RGB  textures are available", LOCATION};
  }
  const GLint bytesPerPixel = GL_RGBA == format ? 4 : 3;

  const GLint size = bytesPerPixel * width * height;
  std::vector<GLubyte> content(static_cast<size_t>(size), 0);

  for (GLint i = 0; i < size; i += bytesPerPixel) {
    size_t idx = static_cast<size_t>(i);
    content[idx] = red;
    content[idx + 1] = green;
    content[idx + 2] = blue;
    content[idx + 3] = 1;
  }

  GLuint name {0};
  glGenTextures(1, &name);
  glBindTexture(GL_TEXTURE_2D, name);
  glTexImage2D(
    GL_TEXTURE_2D
    , 0 // mipmaps
    , internalFormat
    , width
    , height
    , 0 // border
    , format
    , GL_UNSIGNED_BYTE
    , content.data());
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return name;
}

unsigned int TextureLoader::loadFromFile(const char* filePath, GLenum format, GLint internalFormat)
{
  if (GL_RGBA != format && GL_RGB != format) {
    throw Exception{"Wrong format. Only uncompressed GL_RGBA and GL_RGB  textures are available", LOCATION};
  }
  const GLint bytesPerPixel = GL_RGBA == format ? 4 : 3;

  GLint w = 0;
  GLint h = 0;
  GLint n = 0;
  auto content = stbi_load(filePath, &w, &h, &n, bytesPerPixel);

  if (nullptr == content) {
    throw Exception{"Image " + std::string(filePath) + " not found ", LOCATION};
  }

  GLuint name {0};
  glGenTextures(1, &name);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, name);
  glTexImage2D(
    GL_TEXTURE_2D
    , 0 // mipmaps
    , internalFormat
    , w
    , h
    , 0 // border
    , format
    , GL_UNSIGNED_BYTE
    , content);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  free(content);
  return name;
}

} // namespace rwc
