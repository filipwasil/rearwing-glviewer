#pragma once

/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <Vulkan.hpp>

namespace rwc {

class Shader final {
 public:

  Shader();

  ~Shader();

  Shader(const Shader&) = delete;

  Shader& operator=(const Shader&) = delete;

  Shader(Shader&&) = default;

  Shader& operator=(Shader&&) = default;
};

} // namespace rwc
