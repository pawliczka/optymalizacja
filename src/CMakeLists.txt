cmake_minimum_required(VERSION 2.8)

project(Optymalizacja)

file(GLOB_RECURSE appSrc ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE appHeader ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library(${PROJECT_NAME}-lib ${appSrc} ${appHeader})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
