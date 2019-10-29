#pragma once

#include <Config.hpp>
#include <ConfigConstraints.hpp>

namespace rwc
{

#define GLFW_INCLUDE_ES3
static constexpr int GLES_MAJOR_VERSION = 3;
static constexpr int GLES_MINOR_VERSION = 0;

}

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace rwc
{
    static const unsigned DIFFUSE_TEXTURE_UNIT = GL_TEXTURE0 + DIFFUSE_TEXTURE_UNIT_UNIFORM;
}

#define gladLoader gladLoadGLES2Loader
