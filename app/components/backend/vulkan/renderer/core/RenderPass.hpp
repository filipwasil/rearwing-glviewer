#pragma once

/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <Vulkan.hpp>

namespace rwc {

class RenderPass final {
 public:

  RenderPass();

  ~RenderPass();

  RenderPass(const RenderPass&) = delete;

  RenderPass& operator=(const RenderPass&) = delete;

  RenderPass(RenderPass&&) = default;

  RenderPass& operator=(RenderPass&&) = default;
};

} // namespace rwc
