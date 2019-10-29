cmake_minimum_required(VERSION 3.10.0)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/compilers/clang.cmake)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/compilers/gcc.cmake)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/compilers/msvc.cmake)
endif ()
