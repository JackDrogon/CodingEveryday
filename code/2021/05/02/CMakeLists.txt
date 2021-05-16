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

enable_testing()

add_subdirectory(src)
