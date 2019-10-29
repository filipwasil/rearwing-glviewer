#pragma once

/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <Vulkan.hpp>

namespace rwc {

struct Texture {
  VkSampler mSampler;
  VkImage mImage;
  VkImageLayout mImageLayout;
  VkDeviceMemory mMemory;
  VkImageView mView;
  int32_t mWidth;
  int32_t mHeight;
};

} // namespace rwc
