cmake_minimum_required(VERSION 3.28)
project(EXAMPLE_PROJECT)

add_library(example_static_library STATIC)
add_library(example_shared_library SHARED)
add_executable(example_executable)

target_sources(example_static_library
    PRIVATE
        example.cpp
    PUBLIC
        FILE_SET exampleHeaders
        TYPE HEADERS
        FILES
            example.hpp
)

target_sources(example_shared_library
    PRIVATE
        example.cpp
    PUBLIC
        FILE_SET exampleHeaders
        TYPE HEADERS
        FILES
            example.hpp
)

target_link_libraries(example_executable PRIVATE example_static_library)
target_sources(example_executable PRIVATE main.cpp)
