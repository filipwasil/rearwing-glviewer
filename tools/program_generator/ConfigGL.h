#pragma once

#include "Config.h"

namespace rwc
{

#if defined(BACKEND_GLES20)
#define GLFW_INCLUDE_ES2
#elif defined(BACKEND_GLES30)
#define GLFW_INCLUDE_ES3
#endif

}
