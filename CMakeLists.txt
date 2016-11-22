cmake_minimum_required(VERSION 2.8)
project(logger)
add_definitions("-std=c++11")

include_directories(${CMAKE_SOURCE_DIR})
add_executable(example example.cc)
