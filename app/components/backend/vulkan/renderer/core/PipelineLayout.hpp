#pragma once

/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <Vulkan.hpp>

namespace rwc {

class PipelineLayout final {
 public:

  PipelineLayout();

  ~PipelineLayout();

  PipelineLayout(const PipelineLayout&) = delete;

  PipelineLayout& operator=(const PipelineLayout&) = delete;

  PipelineLayout(PipelineLayout&&) = default;

  PipelineLayout& operator=(PipelineLayout&&) = default;
};

} // namespace rwc
