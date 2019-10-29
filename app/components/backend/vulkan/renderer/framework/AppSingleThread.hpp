#pragma once

/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <framework/Framework.hpp>

namespace rwc {

class AppSingleThread final : public Framework {
 public:
  AppSingleThread(const char* appName, unsigned int width, unsigned int height);

  ~AppSingleThread();

  void queueCommandBuffers();

  AppSingleThread(const AppSingleThread&) = delete;

  AppSingleThread& operator=(const AppSingleThread&) = delete;

  AppSingleThread(AppSingleThread&&) = default;

  AppSingleThread& operator=(AppSingleThread&&) = default;

 private:
  // empty
};

} // namespace rwc
