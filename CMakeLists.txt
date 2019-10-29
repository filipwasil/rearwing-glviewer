cmake_minimum_required(VERSION 3.10.0)

# -----------------------------------------------
# Project
# -----------------------------------------------

project(rearwing)

# -----------------------------------------------
# Cmake
# -----------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/sanitizers)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/options.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/backend.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/compiler.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/utils.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/logging.cmake)

# -----------------------------------------------
# Applications
# -----------------------------------------------

add_subdirectory(app)

# -----------------------------------------------
# Components
# -----------------------------------------------

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/components)

# -----------------------------------------------
# Tools
# -----------------------------------------------

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tools)

# -----------------------------------------------
# Tests
# -----------------------------------------------

enable_testing()
add_subdirectory(tests)
