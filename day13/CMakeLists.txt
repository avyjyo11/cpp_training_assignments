cmake_minimum_required(VERSION 3.10)

project(day13)
set(CMAKE_CXX_STANDARD 17)
file(GLOB SOURCES "*.cpp")
add_executable(day13 ${SOURCES} main.cpp)