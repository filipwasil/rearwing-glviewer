#pragma once

#include <xcb/xcb.h>
#include <Vulkan.hpp>

namespace rwc {

struct WindowConfig final {
  xcb_connection_t* mConnection;
  xcb_screen_t* mScreen;
  xcb_window_t mWindow;
};

} // namespace rwc
