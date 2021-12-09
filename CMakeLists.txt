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


# docs
if (GEN_DOCS)
    find_package(Doxygen)

    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docsrc/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/docsrc/Doxyfile.out)

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

        add_custom_target(docs
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Generating API Documentation with Doxygen"
                VERBATIM)
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif (GEN_DOCS)

# Test
include(CTest)
enable_testing()
include_directories(test_runner 3rdparty/doctest)
add_executable(test_runner ${SRC_FILES} test/test_runner.cpp test/test_array.cpp test/test_stack.cpp test/test_ring.cpp test/test_heap.cpp)
add_test(all_test test_runner)

# Examples
add_executable(example_array ${SRC_FILES} examples/array.c)
