cmake_minimum_required(VERSION 3.21)

project(iterator_pattern)

# TODO(Drogon): Add cmake config file for all setting

# Basic Config {
set(CMAKE_EXPORT_COMPILE_COMMANDS 1) # Write compile_commands.json
# }

# Ccache {
include (cmake/ccache.cmake)
# }

# CPM.cmake {
set(CPM_DOWNLOAD_VERSION 0.32.0)
include(cmake/cpm-download.cmake)
# }

# Cpp compiler {
set(CMAKE_CXX_STANDARD 20)
# TODO(Drogon): check gcc clang compiler setting
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-poison-system-directories")
# }

enable_testing()

add_subdirectory(src)
