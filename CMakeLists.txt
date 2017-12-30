cmake_minimum_required(VERSION 3.5)
project(fungi_ai)

set(CMAKE_CXX_STANDARD 14)

find_path(FANN_INCLUDE_DIR fann/src/include)
find_path(SPDLOG_INCLUDE_DIR spdlog/include/spdlog)

if ((NOT FANN_INCLUDE_DIR) OR (NOT EXISTS ${FANN_INCLUDE_DIR}))
	execute_process(COMMAND git submodule update --init -- fann WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
	set(FANN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/fann/src/include CACHE PATH "fann include directory")

	include_directories(PUBLIC fann/src/include/)
	include_directories(PUBLIC fann/lib/googletest/include/)

	add_subdirectory(fann/)
endif()

if ((NOT SPDLOG_INCLUDE_DIR) OR (NOT EXISTS ${SPDLOG_INCLUDE_DIR}))
	execute_process(COMMAND git submodule update --init -- spdlog WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

	include_directories(PUBLIC spdlog/include/spdlog/)
endif()

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -g" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=undefined -g" )

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

file(GLOB_RECURSE LIB_SRC lib/*.cpp)
file(GLOB_RECURSE LIB_HEADER lib/*.hpp)

add_library(fungilib ${LIB_SRC} ${LIB_HEADER})

include_directories("lib/")

add_executable(fungi_ai app/fungi_ai.cpp)
target_link_libraries(fungi_ai fungilib fann)
