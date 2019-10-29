/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <framework/AppMultiThread.hpp>

namespace rwc {

AppMultiThread::AppMultiThread(const char* appName, unsigned int width, unsigned int height)
  : Framework {appName, width, height} {
  // empty
}

AppMultiThread::~AppMultiThread() {

}

void AppMultiThread::queueCommandBuffers() {
  queueCommandBuffersClearScreen();
}

} // namespace rwc