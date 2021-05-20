cmake_minimum_required(VERSION 3.21)

project(iterator_pattern)

# TODO(Drogon): Add cmake config file for all setting

# Basic Config {
set(CMAKE_EXPORT_COMPILE_COMMANDS 1) # Write compile_commands.json
# }


# Cpp compiler {
set(CMAKE_CXX_STANDARD 20)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")  # MATCHES so we get both Clang and AppleClang
	set(CXX_FLAGS ${CMAKE_CXX_FLAGS} -Weverything -Werror -Wno-c++98-compat -Wno-poison-system-directories)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall -Werror)
endif()
# }

# Linter {
set(LINTER_WRAPPER "${CMAKE_SOURCE_DIR}/dev-tools/linter_wrapper")
set(CMAKE_CXX_CPPCHECK "${LINTER_WRAPPER}" "cppcheck")
set(CMAKE_CXX_CPPLINT "${LINTER_WRAPPER}" "cpplint")
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${LINTER_WRAPPER}" "include-what-you-use")
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	set(CMAKE_LINK_WHAT_YOU_USE TRUE)
endif()

set(CMAKE_CXX_CLANG_TIDY "${LINTER_WRAPPER}" "clang-tidy")
set(CLANG_TIDY_CONF_FILE "${CMAKE_SOURCE_DIR}/.clang-tidy")
file(SHA1 ${CLANG_TIDY_CONF_FILE} clang_tidy_sha1)
set(CLANG_TIDY_DEFINITIONS "CLANG_TIDY_SHA1=${clang_tidy_sha1}")
unset(clang_tidy_sha1)
configure_file(${CLANG_TIDY_CONF_FILE} ${CLANG_TIDY_CONF_FILE} COPYONLY)
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
