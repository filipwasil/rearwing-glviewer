cmake_minimum_required(VERSION 3.10.0)

aux_source_directory(. SOURCES)

add_library(factories STATIC ${SOURCES})

include_directories(
        ${REAR_INCLUDE_PATH}
        ${REAR_RENDERER_INCLUDE_PATH}
        ${REAR_LOADERS_PATH}
        ${REAR_BACKEND_INCLUDE_PATH}
        ${REAR_CONFIG_INCLUDE_PATH}
        ${REAR_UTILS_INCLUDE_PATH}
        ${REAR_FACTORIES_INCLUDE_PATH}
        ${REAR_SCENEGRAPH_INCLUDE_PATH}
)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-zero-as-null-pointer-constant")

set_target_properties(factories PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )

target_link_libraries(factories backend)
