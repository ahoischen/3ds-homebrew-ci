cmake_minimum_required(VERSION 2.8.7)

project(libfoo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)
find_package(Git REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(Tools3DS)
find_package(CTRULIB REQUIRED)

###
### Library build config
###

set(LIBFOO_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)
set(LIBFOO_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LIBFOO_TEST_DIR ${PROJECT_SOURCE_DIR}/tests)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/external)

file(GLOB LIBFOO_SOURCE_FILES ${LIBFOO_SOURCE_DIR}/*.cpp)
include_directories(${LIBFOO_INCLUDE_DIR})
add_library(foo ${LIBFOO_SOURCE_FILES})

###
### TEST CONFIG
###
option(LIBFOO_BUILD_TESTS "Indicates whether tests should be built." ON)
if (LIBFOO_BUILD_TESTS)
    file(GLOB LIBFOO_TEST_FILES ${LIBFOO_TEST_DIR}/*.cpp)

    # Includes Catch in the project:
    add_subdirectory(${EXT_PROJECTS_DIR}/catch)
    include_directories(${CATCH_INCLUDE_DIR})

    add_definitions(-DCATCH_CONFIG_NO_POSIX_SIGNALS)
    add_executable(test_runner ${LIBFOO_TEST_FILES})
    add_dependencies(test_runner catch foo)
    target_include_directories(test_runner PRIVATE ${CATCH_INCLUDE_DIR})
    target_link_libraries(test_runner foo 3ds::ctrulib)

    add_3dsx_target(test_runner NO_SMDH)
endif()