//#include "../Window.hpp"
//
//namespace rwc {
//
//Window::Window(const char* name, unsigned int Width, unsigned int Height)
//  : mConfig { name } {
//  // empty
//}
//
//Window::~Window() {
//  // empty
//}
//
//const std::array<const char*, 3> Window::getExtensions() {
//  return std::array<const char*, 3> {
//    VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
//    VK_KHR_SURFACE_EXTENSION_NAME,
//    VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
//  };
//}
//
//} // namespace rwc