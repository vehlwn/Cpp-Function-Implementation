cmake_minimum_required(VERSION 3.10)

project(Cpp-Function-Implementation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} Function.h main.cpp)
