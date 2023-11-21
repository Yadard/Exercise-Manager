cmake_minimum_required(VERSION 3.13) 
project(Listas C)                

include_directories(${CMAKE_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

message("FOO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

add_subdirectory(lib)
add_subdirectory(src)
