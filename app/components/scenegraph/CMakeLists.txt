cmake_minimum_required(VERSION 3.10.0)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/nodes NODES_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/widgets WIDGETS_SOURES)

add_library(scenegraph STATIC ${SOURCES} ${WIDGETS_SOURES} ${NODES_SOURCES})

include_directories(${REAR_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${REAR_UTILS_INCLUDE_PATH})
include_directories(${REAR_RENDERER_INCLUDE_PATH})
include_directories(${REAR_FACTORIES_PATH})
include_directories(${REAR_CONFIG_INCLUDE_PATH})
include_directories(${REAR_SPDLOG_INCLUDE_PATH})

set_property(TARGET backend PROPERTY POSITION_INDEPENDENT_CODE ON)

set_target_properties(scenegraph PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
