cmake_minimum_required(VERSION 3.10.0)

add_subdirectory(${REAR_BACKEND_PATH})
add_subdirectory(${REAR_RENDERER_PATH})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/scenegraph)
add_subdirectory(${REAR_LOADERS_PATH})
add_subdirectory(${REAR_FACTORIES_PATH})

include_directories(${REAR_INCLUDE_PATH})
