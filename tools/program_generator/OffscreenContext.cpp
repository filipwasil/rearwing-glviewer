#include "ConfigGL.h"
#include "Exception.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>
#include <iostream>

#include "OffscreenContext.hpp"

namespace rwc
{

OffscreenContext::OffscreenContext()
  : mGenerator{}
{
  glfwInit();

  const int OPENGL_API = GLFW_OPENGL_ES_API;
  const int OPENGL_API_MAJOR_VERSION = 3;
  const int OPENGL_API_MINOR_VERSION = 0;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_API_MAJOR_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_API_MINOR_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CLIENT_API, OPENGL_API);
  glfwWindowHint(GLFW_RESIZABLE, false);
  glfwWindowHint(GLFW_VISIBLE, false);

  GLFWwindow* window = glfwCreateWindow(1, 1, "OffscreenGenerator", nullptr, nullptr);

  glfwMakeContextCurrent(window);

#ifdef BACKEND_GL41
  if (!gladLoadGL()) {
        return;
    }
#elif defined(BACKEND_GLES30)
  if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)) {
    throw OffscreenContextException{"OpenGL ES 30 failed to initialize"};
  }
#elif defined(BACKEND_GLES20) || defined(BACKEND_GLES30)
  if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)) {
        throw OffscreenContextException{"OpenGL ES 20 failed to initialize"};
    }
    glGetProgramBinaryOES = (PFNGLGETPROGRAMBINARYOESPROC)getAddress("glGetProgramBinaryOES");
    if (glGetProgramBinaryOES == nullptr) {
        throw OffscreenContextException{"OpenGL ES extension glGetProgramBinaryOES failed to initialize"};
    }
    glProgramBinaryOES = (PFNGLPROGRAMBINARYOESPROC)getAddress("glProgramBinaryOES");
    if (glProgramBinaryOES == nullptr) {
        throw OffscreenContextException{"OpenGL ES extension glProgramBinaryOES failed to initialize"};
    }
#endif

  const GLubyte* vendor = glGetString(GL_VENDOR);
  if (vendor != nullptr) {
    std::cout << "OpenGL vendor: " << vendor << "\n";
  }

  const GLubyte* renderer = glGetString(GL_RENDERER);
  if (renderer != nullptr) {
    std::cout << "OpenGL renderer: " << renderer << "\n";
  }

  const GLubyte* version = glGetString(GL_VERSION);
  if (version != nullptr) {
    std::cout << "OpenGL version: " << version << "\n";
  }

  const GLubyte* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);
  if (glsl != nullptr) {
    std::cout << "OpenGL glsl vendor: " << glsl << std::endl;
  }

  GLint formatsCount = 0;
  glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS_OES, &formatsCount);
  std::cout << "GL_NUM_PROGRAM_BINARY_FORMATS:" << formatsCount << std::endl;

  GLint format = 0;
  glGetIntegerv(GL_PROGRAM_BINARY_FORMATS_OES, &format);
  std::cout << "GL_PROGRAM_BINARY_FORMATS:" << format << "\n\nGeneration context initialized" << std::endl;
}

void OffscreenContext::generateProgramBinary(
  const std::string& fragmentShaderPath
  , const std::string& vertexShaderPath
  , const std::string& programBinaryPath
  , const std::string& prefixPath
  , const std::string& outputPath)
{
  try {
    const std::string fs = prefixPath + fragmentShaderPath;
    const std::string vs = prefixPath + vertexShaderPath;
    const std::string pb = outputPath + programBinaryPath;
    mGenerator->generate(fs.c_str(), vs.c_str(), (pb).c_str());
  } catch (const ProgramGeneratorException & ex) {
    std::cout << "ProgramGeneratorException caught!!! " << ex.what() << std::endl;
  }
  std::cout << "Generated program binary: " << programBinaryPath << std::endl;
}

OffscreenContext::~OffscreenContext()
{
  glfwTerminate();
}

} // namespace rwc
