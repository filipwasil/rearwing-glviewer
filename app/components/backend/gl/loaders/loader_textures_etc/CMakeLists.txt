cmake_minimum_required(VERSION 3.10.0)

add_subdirectory(etc2comp)

add_library(loader_textures_etc ETCTextureLoader.cpp)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast")

include_directories(
    ${REAR_UTILS_INCLUDE_PATH}
    ${REAR_BACKEND_INCLUDE_PATH}
    ${REAR_INCLUDE_PATH}
    ${REAR_CONFIG_INCLUDE_PATH}
    etc2comp/Etc
    etc2comp/EtcCodec)