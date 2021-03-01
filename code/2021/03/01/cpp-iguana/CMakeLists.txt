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

# sample
add_executable(sample sample.cc)
target_compile_features(sample PRIVATE cxx_std_17)
target_link_libraries(sample iguana)

# json
add_executable(json json.cc)
target_compile_features(json PRIVATE cxx_std_17)
target_link_libraries(json iguana)

# msgpack
add_executable(msgpack msgpack.cc)
target_compile_features(msgpack PRIVATE cxx_std_17)
target_link_libraries(msgpack iguana)

#}
