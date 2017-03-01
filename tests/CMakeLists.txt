cmake_minimum_required(VERSION 2.8)

project(Optymalizacja-ut)

# file(GLOB_RECURSE testMocks ${CMAKE_CURRENT_SOURCE_DIR}/application/*.hpp)
file(GLOB_RECURSE testSrc ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

link_libraries(gtest)

add_executable(${PROJECT_NAME} ${testSrc})
target_link_libraries(${PROJECT_NAME} Optymalizacja-lib pthread)
