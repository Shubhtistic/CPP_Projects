cmake_minimum_required(VERSION 3.14)
project(LogAnalyzer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Find Required Libraries ---
# This is the best practice for finding system libraries.
# CMake will search for libcurl and its development files.
find_package(CURL REQUIRED)

# The standard regex library sometimes requires linking against the threads library.
# This finds it in a portable way.
find_package(Threads REQUIRED)

# --- Define the Executable ---
# Creates an executable named "log_analyzer" from your source files.
# Update this list as you add new .cpp files.
add_executable(log_analyzer
    src/main.cpp
    src/LogParser.cpp
    src/LogStore.cpp
    src/LogAnalyzer.cpp
)

# Tells the compiler where to find your header files.
target_include_directories(log_analyzer PRIVATE include)

# --- Link the Libraries ---
# This links your executable against the libraries we found.
target_link_libraries(log_analyzer PRIVATE
    CURL::libcurl
    Threads::Threads
)