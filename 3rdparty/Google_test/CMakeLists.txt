# 'Google_test' is the subproject name
project(Google_tests)

set(CMAKE_CXX_FLAGS --coverage)
set(CMAKE_C_FLAGS --coverage)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB TEST_FILES ../../test/*/*.cpp)
file(GLOB SRC_FILES ../../src/*.c)

# 'Google_Tests_run' is the target name
add_executable(Google_Tests_run ${TEST_FILES} ${SRC_FILES})
target_link_libraries(Google_Tests_run gtest gtest_main)
