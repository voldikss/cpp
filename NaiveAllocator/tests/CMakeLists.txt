cmake_minimum_required(VERSION 3.18)

project(NaiveAllocator_tests)

add_executable(NaiveAllocator_tests src/main.cpp)
target_link_libraries(NaiveAllocator_tests NaiveAllocator)

set(WARNING -Wall)
target_compile_options(NaiveAllocator_tests PRIVATE ${WARNING})
