#include <Log.hpp>
#include <Vulkan.hpp>
#include <cstdio>
#include <cassert>
#include <stdexcept>

namespace rwc
{

void logC(const std::string& msg, unsigned int res) {
  if (res != VK_SUCCESS) {
    throw std::runtime_error(msg);
  }
}

void logD(const std::string& msg) {
  printf("%s\n", msg.c_str());
}

void logF(const std::string& msg) {
  logD(msg);
  throw std::runtime_error(msg);
}

void logImageUsageFlags(unsigned int flags) {
  if (flags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) {
    logD("Image usage transfer src is supported");
  }

  if (flags & VK_IMAGE_USAGE_TRANSFER_DST_BIT) {
    logD("Image usage transfer dest is supported");
  }

  if (flags & VK_IMAGE_USAGE_SAMPLED_BIT) {
    logD("Image usage sampled is supported");
  }

  if (flags & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) {
    logD("Image usage color attachment is supported");
  }

  if (flags & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) {
    logD("Image usage depth stencil attachment is supported");
  }

  if (flags & VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT) {
    logD("Image usage transient attachment is supported");
  }

  if (flags & VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT) {
    logD("Image usage input attachment is supported");
  }
}

} // namespace rwe