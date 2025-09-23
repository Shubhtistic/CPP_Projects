
cmake_minimum_required(VERSION 3.10)

# this defines my projects name 
project(FinancialTradingSimulation CXX)

# i have used c++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This command creates our final executable program, named "TradingSim"
# All the .cpp file paths are with "src/" so CMake knows where to find them.
add_executable(TradingSim
    src/main.cpp
    src/Portfolio.cpp
    src/Stock.cpp
    src/Bond.cpp
)

# This now tells our "TradingSim" target to
# look for header files (.h) inside the "include" directoryy
target_include_directories(TradingSim PRIVATE include)