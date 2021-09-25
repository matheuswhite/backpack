cmake_minimum_required(VERSION 3.13)

SET(CMAKE_C_STANDARD 99)

project(backpack)

include_directories(backpack src/include)

file(GLOB SRC_FILES src/*.c)

add_library(backpack STATIC ${SRC_FILES})

file(GLOB TEST_FILES test/*.cpp)

add_executable(all_test ${SRC_FILES} ${TEST_FILES})

enable_testing()

add_test(all_test all_test)
