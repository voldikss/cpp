cmake_minimum_required(VERSION 3.18)
project(NaiveAllocator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(NaiveAllocator INTERFACE)
target_include_directories(NaiveAllocator INTERFACE include/)
add_library(voldikss::NaiveAllocator ALIAS NaiveAllocator)

add_subdirectory(tests)
