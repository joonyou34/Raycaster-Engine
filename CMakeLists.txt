cmake_minimum_required(VERSION 4.1)

project(BobCaster)

option(ENABLE_DEBUG_FEATURES "Enables debug features" OFF)


set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/headers")
set(INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(BINARIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(LIBRARIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")


set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARIES_DIR})

# temporarily we will just glob_recurse
FILE(GLOB_RECURSE ${PROJECT_NAME}_SRC CONFIGURE_DEPENDS
    "${SOURCES_DIR}/*.c"
)

# temporarily we will just glob_recurse
FILE(GLOB_RECURSE ${PROJECT_NAME}_STATICSLIBS CONFIGURE_DEPENDS
    "${LIBRARIES_DIR}/*.a"
)

add_executable(${PROJECT_NAME}_EXE)

target_sources(${PROJECT_NAME}_EXE
    PRIVATE ${${PROJECT_NAME}_SRC}
)

target_include_directories(${PROJECT_NAME}_EXE
    PRIVATE
    "${INCLUDES_DIR}"
    "${HEADERS_DIR}"
)

target_link_libraries(${PROJECT_NAME}_EXE
    PRIVATE
    ${${PROJECT_NAME}_STATICSLIBS}
    opengl32
    glu32
)


if(ENABLE_DEBUG_FEATURES)
    target_compile_definitions(BobCaster_EXE PRIVATE DEBUG_FEATURES)
endif()