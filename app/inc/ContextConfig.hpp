#pragma once

namespace rwc
{

/*!
 * @struct ContextConfig
 *
 * @brief This class encapsulates information how to create a screen
 */
struct ContextConfig final {
/*!
 * @brief index of the monitor to use
 */
  int mMonitorIdx{0};

/*!
 * @brief indicates if the window should be full screen
 */
  bool mIsFullScreen{true};

/*!
 * @brief screen width, will be overwritten by max monitor resolution if "-1" will be passed
 */
  int mScreenWidth{NATIVE_SCREEN_SIZE_ID};

/*!
 * @brief screen height, will be overwritten by max monitor resolution if "-1" will be passed
 */
  int mScreenHeight{NATIVE_SCREEN_SIZE_ID};

/*!
 * @brief name window name
 */
  const char* mScreenName{"empty"};

/*!
 * @brief use this value as window width or height to use native screen resolution
 */
  static constexpr int NATIVE_SCREEN_SIZE_ID = -1;
};

} // namespace rwc
