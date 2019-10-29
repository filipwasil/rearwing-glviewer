cmake_minimum_required(VERSION 3.10.0)

aux_source_directory(. SOURCES)

add_library(loader_textures_raw STATIC ${SOURCES})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-qual")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-align")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-zero-as-null-pointer-constant")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-strict-overflow")

include_directories(
        ${REAR_UTILS_INCLUDE_PATH}
        ${REAR_BACKEND_INCLUDE_PATH}
        ${REAR_CONFIG_INCLUDE_PATH}
)
