#pragma once

#include <Vulkan.hpp>

namespace rwc {

struct WindowConfig final {
  WindowConfig(const char* name);
  ~WindowConfig();
  HINSTANCE mHinstance;
  HWND mHwnd;
  std::wstring mAppName;
};

} // namespace rwc
