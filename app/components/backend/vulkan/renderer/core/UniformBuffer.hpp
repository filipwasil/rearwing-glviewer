#pragma once

/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <Vulkan.hpp>
#include <core/BufferData.hpp>

namespace rwc {

struct UniformBuffer final {
  BufferData mBufferData{};
};

} // namespace rwc
