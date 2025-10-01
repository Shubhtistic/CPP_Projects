cmake_minimum_required(VERSION 3.10)

# this defines my projects name 
project(trading_sim CXX)

# i have used c++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This command creates our final executable program, named "trading_sim"
# All the .cpp file paths are with "src/" so cmake knows where to find them.
add_executable(trading_sim
    src/main.cpp
    src/Portfolio.cpp
    src/Stock.cpp
    src/Bond.cpp
    src/Simulation.cpp
)

# This now tells our "trading_sim" target to
# look for header files (.h) inside the "include" directory
target_include_directories(trading_sim PRIVATE include)

# when we run our program the csv file will be in the root directory so our program won't be able to find it
# but using this we copy the file to the build directory
# so when we run the program it will be able to find it
file(COPY market_assets.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

