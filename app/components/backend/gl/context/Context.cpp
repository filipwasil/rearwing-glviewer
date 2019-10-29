#include <Exception.hpp>
#include <GLContext.hpp>

#include "ConfigGL.hpp"

namespace rwc
{

GLContext::GLContext()
  : Context { { 0, true, ContextConfig::NATIVE_SCREEN_SIZE_ID, ContextConfig::NATIVE_SCREEN_SIZE_ID, "Rear Wing Core"} }
{
  if (!gladLoader(reinterpret_cast<GLADloadproc>(mGetProcAddress)))
  {
    throw Exception{"Failed to initialize extensions", LOCATION};
  }
}

GLContext::~GLContext() = default;

void GLContext::onPreloadResources()
{
  // empty
}

void GLContext::onPreloadSceneGraph()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBlendEquation(GL_FUNC_ADD);
  glClearDepthf(1.0);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  glFrontFace(GL_CW);
}

} // namespace rwc
