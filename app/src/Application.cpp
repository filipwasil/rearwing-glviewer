#include "Application.hpp"

#include <GLPreview.hpp>

namespace rwc
{

Application::Application()
{
  mScreen = std::make_unique<GLPreview>();
}

void Application::runBackgroundContext()
{
  mScreen->setupThreadContext(Context::Type::Offscreen);
}

void Application::runRenderContext()
{
  mScreen->setupThreadContext(Context::Type::Render);
}

void Application::runRenderLoop()
{
  if (mScreen)
  {
    mScreen->preload();
    mScreen->log();
    mScreen->runRenderLoop();
  }
}

void Application::stopRenderLoop()
{
  if (mScreen)
  {
    mScreen->stopRenderLoop();
  }
}

} // namespace rwc
