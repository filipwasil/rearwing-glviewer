cmake_minimum_required(VERSION 3.10.0)

aux_source_directory(. REAR_RENDERER_SOURCES)

add_library(renderer STATIC ${REAR_RENDERER_SOURCES})

include_directories(
    ${REAR_RENDERER_PATH}
    ${REAR_BACKEND_INCLUDE_PATH}
    ${REAR_CONFIG_INCLUDE_PATH}
    ${REAR_UTILS_INCLUDE_PATH}
)

set_target_properties(renderer PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )

target_link_libraries(renderer backend)
