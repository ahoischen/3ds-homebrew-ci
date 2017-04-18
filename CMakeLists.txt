cmake_minimum_required(VERSION 2.8.7)

project(libfoo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)
find_package(Git REQUIRED)

###
### Library build config
###

set(LIBFOO_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)
set(LIBFOO_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LIBFOO_TEST_DIR ${PROJECT_SOURCE_DIR}/tests)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/external)

file(GLOB LIBFOO_SOURCE_FILES ${LIBFOO_SOURCE_DIR}/*.cpp)
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
    enable_testing(true)  # Enables unit-testing.

    message("Catch include dir: ${CATCH_INCLUDE_DIR}")
    message("Libfoo test files: ${LIBFOO_TEST_FILES}")
    add_executable(libfoo_test ${LIBFOO_TEST_FILES})
    add_dependencies(libfoo_test catch)
    target_include_directories(libfoo_test PRIVATE ${CATCH_INCLUDE_DIR})
    target_link_libraries(libfoo_test foo)
    add_test(NAME LibFoo_Test COMMAND libfoo_test)
endif()