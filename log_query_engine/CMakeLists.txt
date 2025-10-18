cmake_minimum_required(VERSION 3.14)
project(LogQueryEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The standard regex and thread libraries sometimes require explicit linking.
# This finds the necessary threads library in a portable way.
find_package(Threads REQUIRED)



add_executable(log_query_engine
   src/main.cpp
    src/log_parse_app.cpp
    src/log_query.cpp
    src/log_vector.cpp
    src/simple_log_parser.cpp
)


target_include_directories(log_query_engine PRIVATE include)

target_link_libraries(log_query_engine PRIVATE
    Threads::Threads
)