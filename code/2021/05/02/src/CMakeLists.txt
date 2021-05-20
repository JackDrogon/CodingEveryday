find_package(Catch2 2 REQUIRED)

# Cpp compiler {
set(CMAKE_CXX_STANDARD 20)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")  # MATCHES so we get both Clang and AppleClang
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Werror -Wno-c++98-compat -Wno-poison-system-directories")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()
include_directories(${PROJECT_SOURCE_DIR}/include)
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


add_executable(iterator_pattern_unittest catch_main.cc iterator_pattern_unittest.cc iterator_pattern.cc)
# target_compile_options(iterator_pattern_unittest PRIVATE -Weverything -Wno-c++98-compat -Wno-poison-system-directories)
# target_include_directories(iterator_pattern_unittest PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(iterator_pattern_unittest PRIVATE Catch2::Catch2)

add_executable(iterator_pattern main.cc iterator_pattern.cc)

add_test(iterator_pattern_unittest iterator_pattern_unittest)
