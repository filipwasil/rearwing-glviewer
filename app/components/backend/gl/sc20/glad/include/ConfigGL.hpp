#pragma once

#include <Config.hpp>
#include <ConfigConstraints.hpp>

namespace rwc
{

static constexpr int GLES_MAJOR_VERSION = 2;
static constexpr int GLES_MINOR_VERSION = 0;

}

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace rwc
{
    static const unsigned DIFFUSE_TEXTURE_UNIT = GL_TEXTURE0 + DIFFUSE_TEXTURE_UNIT_UNIFORM;
}

#define gladLoader gladLoadGLSC2Loader
