//
//#include <stdio.h>
//#include <stdlib.h>
//#include <assert.h>
//#include <string.h>
//#include <unistd.h>
//
//#include <window/Window.h>
//#include <Log.h>
//
//namespace rwc {
//
//Window::Window(const char* /*name*/, unsigned int width, unsigned int height)
//  : mCfg {} {
//  mCfg.mConnection = xcb_connect(nullptr, nullptr);
//
//  int error = xcb_connection_has_error(mCfg.mConnection);
//
//  if  (error) {
//    logC("Error opening xcb connection error", static_cast<unsigned int>(error));
//    assert(0);
//  }
//
//  printf("XCB connection opened\n");
//
//  const auto* setup = xcb_get_setup(mCfg.mConnection);
//  xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
//
//  mCfg.mScreen = iter.data;
//
//  printf("XCB screen %p\n", reinterpret_cast<void*>(mCfg.mScreen));
//
//  mCfg.mWindow = xcb_generate_id(mCfg.mConnection);
//
//  xcb_create_window(mCfg.mConnection,
//                    XCB_COPY_FROM_PARENT,
//                    mCfg.mWindow,
//                    mCfg.mScreen->root,
//                    0,
//                    0,
//                    width,
//                    height,
//                    0,
//                    XCB_WINDOW_CLASS_INPUT_OUTPUT,
//                    mCfg.mScreen->root_visual,
//                    0,
//                    nullptr);
//
//  xcb_map_window(mCfg.mConnection, mCfg.mWindow);
//
//  xcb_flush (mCfg.mConnection);
//
//  printf("Window %x created\n", mCfg.mWindow);
//}
//
//Window::~Window() {
//  if (mCfg.mWindow) {
//    xcb_destroy_window(mCfg.mConnection, mCfg.mWindow);
//  }
//
//  if (mCfg.mConnection) {
//    xcb_disconnect(mCfg.mConnection);
//  }
//}
//
//VkSurfaceKHR Window::createSurface(VkInstance& inst) {
//  VkXcbSurfaceCreateInfoKHR surfaceCreateInfo = {};
//  surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
//  surfaceCreateInfo.connection = mCfg.mConnection;
//  surfaceCreateInfo.window = mCfg.mWindow;
//
//  VkSurfaceKHR surface;
//
//  VkResult res = vkCreateXcbSurfaceKHR(inst, &surfaceCreateInfo, nullptr, &surface);
//  logC("vkCreateXcbSurfaceKHR error", res);
//
//  return surface;
//}
//
//const std::array<const char*, 3> Window::getExtensions() {
//  return {
//    VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
//    VK_KHR_SURFACE_EXTENSION_NAME,
//    VK_KHR_XCB_SURFACE_EXTENSION_NAME,
//  };
//}
//
//} // namespace rwc