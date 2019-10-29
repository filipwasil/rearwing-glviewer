cmake_minimum_required(VERSION 3.10.0)

# -----------------------------------------------
# Backend
# -----------------------------------------------

if(REAR_BACKEND_OPENGL_SC_20)
  set(REAR_BACKEND_NAME gl)
  set(REAR_BACKEND_ROOT gl/sc20)
  set(REAR_BACKEND_DEFINITIONS_INCLUDE gl/sc20/glad/include)
elseif(REAR_BACKEND_OPENGL_ES_30)
  set(REAR_BACKEND_NAME gl)
  set(REAR_BACKEND_ROOT gl/es30)
  set(REAR_BACKEND_DEFINITIONS_INCLUDE gl/es30/glad/include)
elseif(REAR_BACKEND_VULKAN)
  set(REAR_BACKEND_NAME vulkan)
  set(REAR_BACKEND_ROOT vulkan/vulkan)
  set(REAR_BACKEND_DEFINITIONS_INCLUDE vulkan/vulkan/include )
endif()

# -----------------------------------------------
# Renderer
# -----------------------------------------------

set(REAR_BACKEND_PATH ${CMAKE_CURRENT_SOURCE_DIR}/app/components/backend/${REAR_BACKEND_ROOT})
set(REAR_BACKEND_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/app/components/backend/${REAR_BACKEND_DEFINITIONS_INCLUDE})
set(REAR_RENDERER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/app/components/backend/${REAR_BACKEND_NAME}/renderer)
set(REAR_LOADERS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/app/components/backend/${REAR_BACKEND_NAME}/loaders)
set(REAR_FACTORIES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/app/components/backend/${REAR_BACKEND_NAME}/factories)
set(REAR_CONTEXT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/app/components/backend/${REAR_BACKEND_NAME}/context)

set(REAR_CONFIG_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/components/config)
