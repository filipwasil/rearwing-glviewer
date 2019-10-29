#pragma once

#include <Vulkan.hpp>

namespace rwc {

struct BufferData {
  VkBuffer mBuffer{};
  VkDeviceMemory mMemory{};
  VkDescriptorBufferInfo mDescriptorInfo{};
};

} // namespace rwc