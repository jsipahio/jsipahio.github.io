add_executable(test_format)

target_sources(test_format PRIVATE test_format.cpp)
target_link_libraries(test_format PRIVATE logger_static_lib)

add_executable(test_logger)

target_sources(test_logger PRIVATE test_log.cpp)
target_link_libraries(test_logger PRIVATE logger_static_lib)
