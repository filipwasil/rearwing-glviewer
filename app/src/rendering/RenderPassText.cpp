
#include "rendering/RenderPassText.hpp"
#include "ConfigGL.hpp"

namespace rwc
{

void RenderPassText::preRender()
{
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBlendEquation(GL_FUNC_ADD);
}

void RenderPassText::postRender()
{
  // empty
}

} // namespace rwc
