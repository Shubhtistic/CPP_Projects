
# use "make todo_app" with cmake
add_executable(todo_app
    src/main.cpp
    src/console.cpp
    src/todo_header.cpp

)

# tells the target where to find the header files
target_include_directories(todo_app PRIVATE include)

# Link the nlohmann_json library from the main txt file
# only to this specific target.
target_link_libraries(todo_app PRIVATE nlohmann_json::nlohmann_json)
