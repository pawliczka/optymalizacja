cmake_minimum_required(VERSION 2.8)


set(CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -Werror -pedantic-errors")

add_subdirectory(src)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(tests)
