

#include <Exception.hpp>
#include <GLContext.hpp>

#include "ConfigGL.hpp"

namespace rwc
{

GLContext::GLContext()
  : Context { { 0, true, ContextConfig::NATIVE_SCREEN_SIZE_ID, ContextConfig::NATIVE_SCREEN_SIZE_ID, "Rear Wing Core"} }
{
  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
}

GLContext::~GLContext() = default;

void GLContext::onPreloadResources()
{
  // empty
}

void GLContext::onPreloadSceneGraph()
{
  // empty
}

} // namespace rwc
