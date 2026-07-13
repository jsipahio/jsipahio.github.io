add_library(logger_static_lib STATIC)

target_include_directories(logger_static_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_sources(logger_static_lib 
    PRIVATE
        logger.cpp
        utilities.cpp
)

add_executable(logger)

target_link_libraries(logger PRIVATE logger_static_lib)
target_sources(logger PRIVATE main.cpp)
