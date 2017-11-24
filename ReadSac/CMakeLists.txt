cmake_minimum_required(VERSION 3.8)
project(ReadSac)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES SacIO.cpp SacIO.hpp main.cpp)

add_executable(ReadSac ${SOURCE_FILES})