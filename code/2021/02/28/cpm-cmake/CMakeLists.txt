cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# create project
project(cpm-cmake)

# add executable
add_executable(test-catch test-catch.cpp)

# add dependencies
include(cmake/CPM.cmake)
CPMAddPackage("gh:catchorg/Catch2@2.5.0")

# link dependencies
target_link_libraries(test-catch Catch2)
