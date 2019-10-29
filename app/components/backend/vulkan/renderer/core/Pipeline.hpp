#pragma once

/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <Vulkan.hpp>

namespace rwc {

class Pipeline final {
 public:

  Pipeline();

  ~Pipeline();

  Pipeline(const Pipeline&) = delete;

  Pipeline& operator=(const Pipeline&) = delete;

  Pipeline(Pipeline&&) = default;

  Pipeline& operator=(Pipeline&&) = default;
};

} // namespace rwc
