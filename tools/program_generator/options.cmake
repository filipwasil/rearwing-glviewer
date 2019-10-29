option(BACKEND_GLES20 "OpenGL ES 2.0 backend active" OFF)
option(BACKEND_GLES30 "OpenGL ES 3.0 backend active" ON)
option(BACKEND_GL41 "OpenGL 4.1 backend active" OFF)

configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/Config.h"
)
