
macro(copy_generated_assets_to_binary_directory target)
  set (ASSETS_GENERATED_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets/generated/")
  set (ASSETS_SHADERS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders")
  set (ASSETS_MODELS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets/repo/models")

  add_custom_target (
      assets_generated
      COMMAND cp -r ${ASSETS_GENERATED_DIRECTORY}/* ${CMAKE_CURRENT_BINARY_DIR}/
  )

  add_custom_target (
      assets_shaders
      COMMAND cp -r ${ASSETS_SHADERS_DIRECTORY} ${CMAKE_CURRENT_BINARY_DIR}/
  )

  add_custom_target (
      assets_repo
      COMMAND cp -r ${ASSETS_MODELS_DIRECTORY} ${CMAKE_CURRENT_BINARY_DIR}/
  )

  add_dependencies (${target} assets_generated assets_shaders assets_repo)
endmacro(copy_generated_assets_to_binary_directory)
