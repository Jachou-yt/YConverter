cmake_minimum_required(VERSION 3.25)
project(YConverter)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(YConverter_ main.cpp)

