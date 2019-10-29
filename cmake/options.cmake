cmake_minimum_required(VERSION 3.10.0)

# -----------------------------------------------
# Backend
# -----------------------------------------------

option(REAR_BACKEND_OPENGL_SC_20 "Using OpenGL SC 2.0 core profile" OFF)
option(REAR_BACKEND_OPENGL_ES_30 "Using OpenGL ES 3.0 core profile" ON)
option(REAR_BACKEND_VULKAN "Using Vulkan backend" OFF)
option(REAR_BACKEND_OPENGL_PC "Using full featured OpenGL PC core profile" OFF)

option(REAR_TEXURES_S3TC "Using S3TC COMPRESSION" OFF)
option(REAR_TEXURES_ETC "Using ETC2 COMPRESSION" OFF)

# -----------------------------------------------
# Tests
# -----------------------------------------------

option(REAR_TESTS "Build with google test tests" OFF)
option(REAR_COVERITY "Build with gcc coverity tests" OFF)
option(REAR_BENCHMARKS "Generate google benchmarks data" OFF)

# -----------------------------------------------
# Config
# -----------------------------------------------

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/components/config/Config.hpp"
)