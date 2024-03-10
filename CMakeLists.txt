cmake_minimum_required(VERSION 3.12)
project(tic-tac-toe)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE sources "main.cpp" "source/*.cpp")
include_directories(source)

add_executable(tic-tac-toe ${sources})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})