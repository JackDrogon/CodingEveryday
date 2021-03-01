cmake_minimum_required(VERSION 3.14 FATAL_ERROR)


# create project
project(cpp-iguana)


# Add dependencies {
include(cmake/CPM.cmake)
CPMAddPackage("gh:qicosmos/iguana#HEAD")

if(iguana_ADDED)
  add_library(iguana INTERFACE IMPORTED)
  target_include_directories(iguana SYSTEM INTERFACE "${iguana_SOURCE_DIR}")
  target_include_directories(iguana SYSTEM INTERFACE "${iguana_SOURCE_DIR}/third_party/msgpack/include")
  target_include_directories(iguana SYSTEM INTERFACE "/usr/local/include") # MACOSX for boost/lexical_cast.hpp
endif()
#}


# Add executable {
add_executable(sample sample.cc)
target_link_libraries(sample iguana)
target_compile_features(sample PRIVATE cxx_std_17)
#}
