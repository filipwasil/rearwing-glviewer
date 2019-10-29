/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <framework/AppSingleThread.hpp>

namespace rwc {

AppSingleThread::AppSingleThread(const char* appName, unsigned int width, unsigned int height)
 : Framework {appName, width, height} {
  // empty
}

AppSingleThread::~AppSingleThread() {

}

void AppSingleThread::queueCommandBuffers() {
  queueCommandBuffersClearScreen();
}

} // namespace rwc