cmake_minimum_required(VERSION 3.28)

project(DSA_CH7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(test_list)
target_sources(test_list PRIVATE test_list.cpp list.hpp)
target_link_libraries(test_list
    PRIVATE 
        GTest::gtest 
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_list)
