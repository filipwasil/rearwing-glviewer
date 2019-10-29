cmake_minimum_required(VERSION 3.10.0)

add_library(backend STATIC ${CMAKE_CURRENT_SOURCE_DIR}/empty.cpp)

include_directories(.)

target_link_libraries(backend ${CMAKE_DL_LIBS})

set_property(TARGET backend PROPERTY POSITION_INDEPENDENT_CODE ON)
