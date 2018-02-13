cmake_minimum_required(VERSION 3.10)
project(testRadix64)

set(CMAKE_CXX_STANDARD 11)

add_executable(testRadix64 main.cpp radix64.cpp includes.cpp)