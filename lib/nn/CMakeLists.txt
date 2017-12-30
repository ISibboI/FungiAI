cmake_minimum_required(VERSION 3.5)
project(fungi_nn)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE LIB_SRC *.cpp)
file(GLOB_RECURSE LIB_HEADER *.hpp)

add_library(fungi_nn ${LIB_SRC} ${LIB_HEADER})
include_directories(..)
target_link_libraries(fungi_nn fungi_game fann)