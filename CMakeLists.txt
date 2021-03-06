cmake_minimum_required(VERSION 3.5)
project(fungi_ai)

set(CMAKE_CXX_STANDARD 14)

SET( CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS} -g" )
SET( CMAKE_EXE_LINKER_FLAGS_DEBUG  "${CMAKE_EXE_LINKER_FLAGS} -g" )

add_compile_options(-march=native)

find_path(FANN_INCLUDE_DIR fann/src/include)
find_path(SPDLOG_INCLUDE_DIR spdlog/include/spdlog)
find_path(NANA_INCLUDE_DIR nana/include)

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

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Og")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -O3 -DNDEBUG")

add_subdirectory(lib/game)
add_subdirectory(lib/nn)
add_subdirectory(lib/evolutional)
add_subdirectory(lib/gui)

file(GLOB_RECURSE LIB_HEADER lib/*.hpp)

include_directories("lib/")

add_executable(fungi_ai app/fungi_ai.cpp)
target_link_libraries(fungi_ai fungi_evolutional)

add_executable(gui app/gui.cpp)
target_link_libraries(gui fungi_gui)

add_executable(evolutional_training app/evolutional_training.cpp)
target_link_libraries(evolutional_training fungi_evolutional)

add_executable(evaluate app/evaluate.cpp)
target_link_libraries(evaluate fungi_nn)
