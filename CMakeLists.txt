cmake_minimum_required(VERSION 3.13)

SET(CMAKE_C_STANDARD 99)

project(backpack)

include_directories(backpack src/include)

file(GLOB SRC_FILES src/*.c)

add_library(backpack STATIC ${SRC_FILES})
