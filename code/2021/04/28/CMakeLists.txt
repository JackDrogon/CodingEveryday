cmake_minimum_required(VERSION 3.21)

project(iterator_pattern)

set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 2 REQUIRED)
add_executable(iterator_pattern_unittest catch_main.cc iterator_pattern_unittest.cc)
target_link_libraries(iterator_pattern_unittest PRIVATE Catch2::Catch2)
