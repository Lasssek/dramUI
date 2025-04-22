cmake_minimum_required(VERSION 3.13)
project(PASJANS)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES 
    "src/*.cc"
)

add_executable(pasjans ${SOURCES})
target_include_directories(pasjans PRIVATE include)