project(tinyobjloader)

cmake_minimum_required(VERSION 2.8.6)

set(tinyobjloader-Source
    loader_models_obj.h
    loader_models_obj.cc
	)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-zero-as-null-pointer-constant")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-class-memaccess")

add_library(loader_models_obj STATIC ${tinyobjloader-Source})
