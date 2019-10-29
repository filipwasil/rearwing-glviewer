cmake_minimum_required(VERSION 3.10.0)

add_subdirectory(loader_models_obj)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/loader_textures_raw)

if(REAR_TEXURES_S3TC)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/loader_textures_s3tc)
endif()

if(REAR_TEXURES_ETC)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/loader_textures_etc)
endif()
