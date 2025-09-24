
# C++ Command-Line To-Do List Application

## 📝 Summary
This is a robust and persistent command-line to-do list application built in modern C++. It features a professional two-tier architecture, robust error handling, and data persistence via a JSON file.

This project is part of my larger C++ portfolio, but is also a complete, standalone application.

---

## ✨ Key Features
- **Full CRUD Functionality**: Create, view, edit, and delete tasks.
- **Persistent Storage**: Task data is automatically saved to `tasks.json` on exit and reloaded on launch using the RAII principle.
- **Task State Management**: Mark tasks as "complete" or "pending."
- **Robust Input Handling**: Resilient to invalid user input, preventing crashes.
- **Stable ID System**: Each task is assigned a permanent, unique ID.

---

## 🛠️ Core Concepts Demonstrated
- **Software Architecture**: Separation of Concerns (`manager` logic vs. `console` UI).
- **C++ & OOP**: Encapsulation, Function Overloading, `const` correctness, STL containers.
- **Data Handling**: JSON Serialization/Deserialization with the `nlohmann/json` library.
- **Error Handling**: `try-catch` blocks for file I/O and JSON parsing errors.
- **Professional Tooling**: A clean, hierarchical CMake build system within a monorepo.

---

## ⚙️ Prerequisites
Please make sure you already have:
- **C++17 compiler** (GCC/Clang/MSVC)
- **CMake** (v3.14+)
- **Git**

The `nlohmann/json` library is automatically fetched by CMake.

---

## 💻 Installation & Setup

### 🔹 Linux And MacOs

- Clone repository:
```bash
git clone https://github.com/shubh4m-2k04/CPP_Projects
cd C++-Projects/todo-app
```

- Create build directory and compile:
```bash
mkdir build && cd build
cmake ..
make
#or 
cmake todo_app
#to only make the todo_app executable file
```

- Run application
```bash
./todo_app
```
The executable file will be in build directory
Or in the folder you used for build

### 🔹 Windows (PowerShell or Developer Command Prompt)
- Clone repository
```bash
git clone https://github.com/shubh4m-2k04/CPP_Projects
cd C++-Projects\todo-app
```

- Create build directory and compile
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

- Run application
```bash
.\Debug\todo_app.exe   # (Visual Studio/MSVC build)
.\todo_app.exe         # (MinGW build)
```
### 📂 Data Persistence

- A tasks.json file is created inside the build directory.

- It is automatically saved on exit and loaded on the next run.


