#pragma once

#ifdef __linux__
#include <window/WindowXCBTraits.hpp>
#elif _WIN32
#include <window/WindowWin32Traits.h>
#else
#error "No window config defined for this OS"
#endif

#include <array>

namespace rwc
{

class Window final {
 public:
  Window(const char* name, unsigned int Width, unsigned int Height);
  ~Window();

  VkSurfaceKHR createSurface(VkInstance& inst);

  const std::array<const char*, 3> getExtensions();

 private:
  WindowConfig mCfg;
};

} // namespace rwc
