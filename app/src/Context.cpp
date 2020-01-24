#include "Context.hpp"
#include "Exception.hpp"
#include <Logger.hpp>

#include "ConfigGL.hpp"

#include <chrono>

namespace rwc
{

Context::Context(const ContextConfig& cfg)
  : mGetProcAddress{glfwGetProcAddress}
{
  if (!glfwInit())
  {
    throw Exception{"Failed to initialize context", LOCATION};
  }

  int monitorsSize = 0;
  auto** monitors = glfwGetMonitors(&monitorsSize);
  if (0 >= monitorsSize || monitorsSize <= cfg.mMonitorIdx)
  {
    throw Exception{"Monitor Id exceeds maximum number of monitors", LOCATION};
  }

  initWindow(monitors, cfg);
  initCallbacks();
}

Context::~Context()
{
  glfwDestroyWindow(mWindow);
  glfwTerminate();
}

void Context::initWindow(GLFWmonitor** monitors, const ContextConfig& cfg)
{
#if defined(REAR_BACKEND_OPENGL_ES_30)
  // empty
#elif defined(REAR_BACKEND_VULKAN)
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);
#endif

  mBackgroundContext = glfwCreateWindow(1, 1, "_", nullptr, mWindow);
  if (nullptr == mBackgroundContext)
  {
    glfwTerminate();
  }

  glfwWindowHint(GLFW_VISIBLE, false);

  if (cfg.mIsFullScreen)
  {
    auto* mode = glfwGetVideoMode(monitors[cfg.mMonitorIdx]);
    if (nullptr != mode)
    {
      mResolution[0] = ContextConfig::NATIVE_SCREEN_SIZE_ID == cfg.mScreenWidth ? mode->width : cfg.mScreenWidth;
      mResolution[1] = ContextConfig::NATIVE_SCREEN_SIZE_ID == cfg.mScreenHeight ? mode->height : cfg.mScreenHeight;
      mWindow = glfwCreateWindow(mResolution[0], mResolution[1], cfg.mScreenName, monitors[cfg.mMonitorIdx], nullptr);
    }
  } else
  {
    mResolution = {static_cast<float>(cfg.mScreenWidth), static_cast<float>(cfg.mScreenHeight)};
    mWindow = glfwCreateWindow(cfg.mScreenWidth, cfg.mScreenHeight, cfg.mScreenName, nullptr, nullptr);
  }

#if defined(REAR_BACKEND_VULKAN)
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

  if (nullptr == mWindow)
  {
    glfwTerminate();
  }
  glfwMakeContextCurrent(mWindow);
}

void Context::initCallbacks()
{
  glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int /*scancode*/, int /*action*/, int /*mods*/) {
    if (!glfwWindowShouldClose(window)) {
      if (GLFW_KEY_ESCAPE == key)
      {
        glfwSetKeyCallback(window, nullptr);
        glfwSetWindowShouldClose(window, true);
      }
    }});
}

void Context::runRenderLoop()
{
  auto begin = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now();

  int fps = 0;
  float fpsMicrosecondsPassed = 0.0f;

  float globalSecondsPassed = 0.0f;

  while (!glfwWindowShouldClose(mWindow))
  {
    end = std::chrono::high_resolution_clock::now();
    float microsecondsPassed = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
    begin = end;
    fpsMicrosecondsPassed += microsecondsPassed;
    globalSecondsPassed += microsecondsPassed;
    if (fpsMicrosecondsPassed >= 1000000.0f)
    {
      fpsMicrosecondsPassed -= 1000000.0f;
      ::spdlog::trace("FPS {}", fps);
      fps = 0;
    }
    else
    {
      fps++;
    }
    glfwPollEvents();
    onRenderFrame(microsecondsPassed * 0.001f);
    glfwSwapBuffers(mWindow);
  }
}

void Context::setupThreadContext(Type contextType)
{
  switch(contextType)
  {
    case Type::Offscreen:
      glfwMakeContextCurrent(mBackgroundContext);
      break;
    case Type::Render:
    case Type::Custom:
    default:
      glfwMakeContextCurrent(mWindow);
      break;
  }
}

void Context::focusOnContext(Type contextType)
{
  switch(contextType)
  {
    case Type::Offscreen:
      glfwFocusWindow(mBackgroundContext);
      break;
    case Type::Render:
    case Type::Custom:
    default:
      glfwFocusWindow(mWindow);
      break;
  }
}


void Context::stopRenderLoop()
{
  glfwSetWindowShouldClose(mWindow, true);
}

void Context::preload()
{
  onPreloadResources();
  onPreloadSceneGraph();
}

void Context::log()
{
  const GLubyte* vendor = glGetString(GL_VENDOR);
  if (nullptr != vendor)
  {
    log::info("OpenGL vendor: {}", vendor);
  }

  const GLubyte* renderer = glGetString(GL_RENDERER);
  if (nullptr != renderer)
  {
    log::info("OpenGL renderer: {}", renderer);
  }

  const GLubyte* version = glGetString(GL_VERSION);
  if (nullptr != version)
  {
    log::info("OpenGL version: {}", version);
  }

  const GLubyte* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);
  if (nullptr != glsl)
  {
    log::info("GLSL version: {}", glsl);
  }

  log::info("");
}

vec2f Context::getResolution()
{
  return mResolution;
}

GLFWwindow* Context::getWindow()
{
  return mWindow;
}

} // namespace rwc
