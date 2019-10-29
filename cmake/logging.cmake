cmake_minimum_required(VERSION 3.11.0)

# -----------------------------------------------
# Paths
# -----------------------------------------------

include(FetchContent)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG v1.3.1
)

FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
    FetchContent_Populate(spdlog)
endif()
set(REAR_SPDLOG_INCLUDE_PATH ${spdlog_SOURCE_DIR}/include)

