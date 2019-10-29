cmake_minimum_required(VERSION 2.8.8)

add_subdirectory(freetype2)

include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}/freetype2/include
)

aux_source_directory(. FONT_GENERATOR_SOURCES)

add_executable(font_generator ${FONT_GENERATOR_SOURCES})

target_link_libraries(font_generator freetype)

set_target_properties(font_generator PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

target_link_libraries(font_generator freetype stdc++fs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-zero-as-null-pointer-constant")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-qual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-strict-overflow")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-align")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast")
