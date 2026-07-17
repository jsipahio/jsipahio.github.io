cmake_minimum_required(VERSION 3.28)

project(EXAMPLE_PROJECT)

add_executable(example_program)
target_sources(example_program PRIVATE example.cpp)
