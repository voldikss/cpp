cmake_minimum_required(VERSION 3.18)

project(SmartPointer_tests)

add_executable(SmartPointer_tests src/main.cpp)
target_link_libraries(SmartPointer_tests SmartPointer)

set(WARNING -Wall)
target_compile_options(SmartPointer_tests PRIVATE ${WARNING})
