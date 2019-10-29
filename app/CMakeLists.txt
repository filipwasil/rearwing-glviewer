cmake_minimum_required(VERSION 3.10.0)

# -----------------------------------------------
# Paths
# -----------------------------------------------

set(REAR_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(REAR_WIDGETS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets)

# -----------------------------------------------
# Sources
# -----------------------------------------------

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src REAR_SLAVE_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/rendering REAR_SLAVE_SOURCES_RENDERPASSES)
aux_source_directory(${REAR_WIDGETS_PATH}/simple_ui REAR_SLAVE_SOURCES_WIDGETS_SIMPLE_UI)

# -----------------------------------------------
# Components
# -----------------------------------------------

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/scenegraph.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/scripts.cmake)

# -----------------------------------------------
# Subdirectories
# -----------------------------------------------

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/components)

# -----------------------------------------------
# Includes
# -----------------------------------------------

include_directories(${REAR_INCLUDE_PATH})
include_directories(${REAR_BACKEND_INCLUDE_PATH})
include_directories(${REAR_LOADERS_PATH})
include_directories(${REAR_SCENEGRAPH_INCLUDE_PATH})
include_directories(${REAR_FACTORIES_PATH})
include_directories(${REAR_UTILS_INCLUDE_PATH})
include_directories(${REAR_RENDERER_INCLUDE_PATH})
include_directories(${REAR_CONFIG_INCLUDE_PATH})
include_directories(${REAR_SPDLOG_INCLUDE_PATH})

# -----------------------------------------------
# Project
# -----------------------------------------------

add_executable(
  app
  ${REAR_SLAVE_SOURCES}
  ${REAR_SLAVE_SOURCES_RENDERPASSES}
  ${REAR_SLAVE_SOURCES_WIDGETS_SIMPLE_UI}
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${REAR_CONTEXT_PATH}/Context.cpp
)

set_target_properties(app PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )

# -----------------------------------------------
# Dependencies
# -----------------------------------------------

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Threads REQUIRED)
find_package(Sanitizers)

# -----------------------------------------------
# Linked libraries
# -----------------------------------------------

target_link_libraries(app
    Threads::Threads
    glfw
    scenegraph
    factories
    backend
    renderer
    loader_models_obj
    ${REAR_LOADER_TEXTURES_COMPRESSED}
    loader_textures_raw
)
add_sanitizers(app)

# -----------------------------------------------
# Scripts
# -----------------------------------------------

copy_generated_assets_to_binary_directory(app)
