cmake_minimum_required(VERSION 3.10.0)

set(PROD_SRC
    ${SLAVE_COMPONENTS}/scenegraph/Moveable.cpp
    ${SLAVE_COMPONENTS}/scenegraph/Scene.cpp
    ${SLAVE_COMPONENTS}/scenegraph/nodes/Node3D.cpp
    ${SLAVE_COMPONENTS}/factories/ProgramObjectFactory.cpp
    ${SLAVE_COMPONENTS}/loaders/loader_textures_raw/TextureLoader.cpp
    ${COMMON_COMPONENTS}/ipc/protocols/RegistrationProtocol.cpp
    ${COMMON_COMPONENTS}/ipc/protocols/HeartBeat.cpp
    ${COMMON_COMPONENTS}/ipc/connections/Connections.cpp
)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/stubs STUBS_SRC)
add_compile_options(
    -Wno-sign-promo
    -Wno-noexcept
)

set(TEST_SRC
    main.cpp 
    tMoveable.cpp
        tTextureLoader.cpp
    tRendererGL.cpp
    tNode3D.cpp
    ${STUBS_SRC}
    protocols/tRegistration.cpp
        )

include_directories(
    ${SLAVE_COMPONENTS}/scenegraph/inc
    ${SLAVE_COMPONENTS}/loaders
    ${COMMON_COMPONENTS}/utils/inc
    ${COMMON_COMPONENTS}/ipc/protocols/inc
    ${COMMON_COMPONENTS}/ipc/transport/inc
    ${COMMON_COMPONENTS}/ipc/connections/inc
    ${COMMON_COMPONENTS}/ipc/inc
    ${REAR_CONFIG_INCLUDE_PATH}
    ${REAR_RENDERER_INCLUDE_PATH}
    ${REAR_BACKEND_INCLUDE_PATH}
    ${REAR_SERIALIZATION_INCLUDE_PATH}
    ${REAR_SPDLOG_INCLUDE_PATH}
    ../frameworks
)

find_package(Sanitizers)

add_executable(unit_tests ${PROD_SRC} ${TEST_SRC})
add_sanitizers(unit_tests)

set_target_properties(unit_tests PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(unit_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
add_test(unit_tests unit_tests)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

target_link_libraries(unit_tests Threads::Threads cereal_tests utils atomic)

