
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(aoc2022)
include(CTest)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
add_subdirectory(src)
add_subdirectory(apps)

add_test(NAME solver01test COMMAND solver01 ${PROJECT_SOURCE_DIR}/input/input01_test)
add_test(NAME solver01main COMMAND solver01 ${PROJECT_SOURCE_DIR}/input/input01)
add_test(NAME solver02test COMMAND solver02 ${PROJECT_SOURCE_DIR}/input/input02_test)
add_test(NAME solver02main COMMAND solver02 ${PROJECT_SOURCE_DIR}/input/input02)

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")

INSTALL(TARGETS solver01)
INSTALL(TARGETS solver02)
