cmake_minimum_required(VERSION 2.8)

project(Optymalizacja-ut)

set(SOURCES
    main.cpp
    DummyTestSuite.cpp
)

link_libraries(gtest)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Optymalizacja-lib pthread)
