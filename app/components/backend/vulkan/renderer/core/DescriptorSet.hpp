#pragma once

/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <Vulkan.hpp>

namespace rwc {

class DescriptorSet final {
 public:

  DescriptorSet();

  ~DescriptorSet();

  DescriptorSet(const DescriptorSet&) = delete;

  DescriptorSet& operator=(const DescriptorSet&) = delete;

  DescriptorSet(DescriptorSet&&) = default;

  DescriptorSet& operator=(DescriptorSet&&) = default;

};

} // namespace rwc
