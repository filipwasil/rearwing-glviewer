cmake_minimum_required(VERSION 3.10.0)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)

find_package(Sanitizers)

add_library(utils STATIC ${SOURCES})
add_sanitizers(utils)

set_property(TARGET utils PROPERTY POSITION_INDEPENDENT_CODE ON)
