cmake_minimum_required(VERSION 3.10.0)

add_library(loader_textures_s3tc STATIC nv_dds.cpp)

include_directories(${REAR_BACKEND_INCLUDE_PATH} ${REAR_CONFIG_INCLUDE_PATH})