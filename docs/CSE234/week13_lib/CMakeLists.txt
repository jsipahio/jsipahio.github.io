cmake_minimum_required(VERSION 3.28)
project(LIBRARY_EXAMPLE)

add_library(example_library)
target_sources(example_library
    PRIVATE
        example.cpp
    PUBLIC
        FILE_SET exampleHeaders
        TYPE HEADERS
        FILES
            example.hpp
)
