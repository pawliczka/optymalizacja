cmake_minimum_required(VERSION 2.8)

project(Optymalizacja)

set(SOURCES

)

add_library(${PROJECT_NAME}-lib ${SOURCES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
