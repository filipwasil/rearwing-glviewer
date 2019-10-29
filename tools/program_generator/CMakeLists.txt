cmake_minimum_required(VERSION 3.10.0)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/options.cmake)

if (BACKEND_GL41)
  set (BACKEND_NAME gl41)
elseif(BACKEND_GLES20)
  set (BACKEND_NAME gles20)
elseif(BACKEND_GLES30)
  set (BACKEND_NAME gles30)
endif()

add_executable(program_generator
    main.cpp
    OffscreenContext.cpp
    ProgramGenerator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/${BACKEND_NAME}/src/glad.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glad/${BACKEND_NAME}/include)

target_link_libraries(program_generator glfw ${CMAKE_DL_LIBS} stdc++fs)

set_target_properties(program_generator PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-align")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-zero-as-null-pointer-constant")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-declarations")

set_property(TARGET program_generator PROPERTY POSITION_INDEPENDENT_CODE ON)

set (CMAKE_EXTRA_INCLUDE_FILES)
