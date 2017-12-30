cmake_minimum_required(VERSION 3.5)
project(fungi_evolutional)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE LIB_SRC *.cpp)
file(GLOB_RECURSE LIB_HEADER *.hpp)

add_library(fungi_evolutional ${LIB_SRC} ${LIB_HEADER})
include_directories(..)
target_link_libraries(fungi_evolutional fungi_nn)