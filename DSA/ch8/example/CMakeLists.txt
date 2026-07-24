cmake_minimum_required(VERSION 3.28)

project(DSA_CH8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(test_set)
target_sources(test_set PRIVATE test_set.cpp set.hpp)
target_link_libraries(test_set
    PRIVATE 
        GTest::gtest 
        GTest::gtest_main
)

add_executable(test_map)
target_sources(test_map PRIVATE test_map.cpp map.hpp)
target_link_libraries(test_map
    PRIVATE 
        GTest::gtest 
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_set)
gtest_discover_tests(test_map)
