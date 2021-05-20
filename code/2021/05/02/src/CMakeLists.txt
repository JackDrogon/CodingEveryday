find_package(Catch2 2 REQUIRED)


add_executable(iterator_pattern_unittest catch_main.cc iterator_pattern_unittest.cc iterator_pattern.cc)
target_compile_options(iterator_pattern_unittest PRIVATE ${CXX_FLAGS})
target_include_directories(iterator_pattern_unittest PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(iterator_pattern_unittest PRIVATE Catch2::Catch2)

add_executable(iterator_pattern main.cc iterator_pattern.cc)
target_compile_options(iterator_pattern PRIVATE ${CXX_FLAGS})
target_include_directories(iterator_pattern PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_test(iterator_pattern_unittest iterator_pattern_unittest)
