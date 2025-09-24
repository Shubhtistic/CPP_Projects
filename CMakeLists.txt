# A safe, portable version that supports modern features like FetchContent.
cmake_minimum_required(VERSION 3.14)

project(C++Portfolio CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Centralized dependncy Management
# By placing FetchContent here, we define a single version of each library for our use
# for the entire portfolio, preventing version conflicts.
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3 # Use a specific, stable version tag
)


FetchContent_MakeAvailable(nlohmann_json)

# CMake will now go inside the todo app folder for its own CMakeLists.txt.
add_subdirectory(todo_app)

#for future
add_subdirectory(financial_trade_simulation)
