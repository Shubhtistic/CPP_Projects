cmake_minimum_required(VERSION 3.14)
project(LogQueryEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The standard regex and thread libraries sometimes require explicit linking.
# This finds the necessary threads library in a portable way.
find_package(Threads REQUIRED)



add_executable(log_query_engine
   
)


target_include_directories(log_query_engine PRIVATE include)

target_link_libraries(log_query_engine PRIVATE
    Threads::Threads
)