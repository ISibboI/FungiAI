cmake_minimum_required(VERSION 3.5)
project(fungi_gui)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE LIB_SRC *.cpp)
file(GLOB_RECURSE LIB_HEADER *.hpp)

add_library(fungi_gui ${LIB_SRC} ${LIB_HEADER})
include_directories(.. ../../nana/include)
target_link_libraries(fungi_gui fungi_game nana)