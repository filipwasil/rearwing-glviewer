
#include "rendering/RenderPassStart.hpp"
#include "ConfigGL.hpp"

namespace rwc
{

void RenderPassStart::preRender()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderPassStart::postRender()
{
  // empty
}

} // namespace rwc
