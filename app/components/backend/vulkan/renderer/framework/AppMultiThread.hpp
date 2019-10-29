#pragma once

/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <framework/Framework.hpp>

namespace rwc {

class AppMultiThread final : public Framework {
 public:
  AppMultiThread(const char* appName, unsigned int width, unsigned int height);

  ~AppMultiThread();

  void queueCommandBuffers();

  AppMultiThread(const AppMultiThread&) = delete;

  AppMultiThread& operator=(const AppMultiThread&) = delete;

  AppMultiThread(AppMultiThread&&) = default;

  AppMultiThread& operator=(AppMultiThread&&) = default;

 private:
  // empty
};

} // namespace rwc
