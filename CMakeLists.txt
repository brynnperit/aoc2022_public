
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(aoc2022)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
add_subdirectory(src)
add_subdirectory(apps)

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")

INSTALL(TARGETS solver01)
INSTALL(TARGETS solver02)
