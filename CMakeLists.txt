cmake_minimum_required(VERSION 3.3)
project(finalassignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp hashing_BST.cpp hashing_BST.h)
add_executable(finalassignment ${SOURCE_FILES})