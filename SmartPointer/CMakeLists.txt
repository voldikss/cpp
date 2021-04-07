cmake_minimum_required(VERSION 3.18)
project(SmartPointer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(SmartPointer INTERFACE)
target_include_directories(SmartPointer INTERFACE include/)

add_subdirectory(tests)
