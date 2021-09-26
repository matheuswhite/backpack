cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(backpack)

option(BUILD_TESTS "Build test executable" OFF)
option(GEN_DOCS "Generate documentation" ON)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if (ENABLE_COVERAGE)
    include(CodeCoverage)

    append_coverage_compiler_flags()
    set(COVERAGE_EXCLUDES "/usr/include/\\*;${CMAKE_SOURCE_DIR}/test/*;${CMAKE_SOURCE_DIR}/3rdparty/doctest/*;${CMAKE_SOURCE_DIR}/examples/*")

    setup_target_for_coverage(NAME coverage EXECUTABLE ctest DEPENDENCIES coverage)
endif (ENABLE_COVERAGE)


include_directories(backpack src/include)
file(GLOB SRC_FILES src/*.c)
add_library(backpack STATIC ${SRC_FILES})


# Test
include(CTest)
enable_testing()
include_directories(test_runner 3rdparty/doctest)
file(GLOB TEST_FILES test/*.cpp)
add_executable(test_runner ${SRC_FILES} ${TEST_FILES} test/test_runner.cpp)
add_test(all_test test_runner)
