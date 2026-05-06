# C++ Command-Line To-Do List

A persistent command-line to-do list application built in modern C++. Features a two-tier architecture, JSON-based data persistence, and robust error handling.

---

## Features

- **Full CRUD** — Create, view, edit, and delete tasks
- **Persistent Storage** — Tasks saved to `tasks.json` on exit, reloaded on next launch (RAII)
- **Task State** — Mark tasks as complete or pending
- **Stable IDs** — Each task gets a permanent unique ID
- **Input Handling** — Resilient to invalid input throughout

---

## Core Concepts

- **Architecture** — Separation of concerns between `manager` (logic) and `console` (UI)
- **OOP** — Encapsulation, function overloading, `const`-correctness, STL containers
- **Data Persistence** — JSON serialization via `nlohmann/json` (auto-fetched by CMake)
- **Error Handling** — `try-catch` for file I/O and JSON parsing errors
- **Build System** — CMake, integrates cleanly into the monorepo structure

---

## Prerequisites

- C++17 compiler (GCC / Clang / MSVC)
- CMake 3.14+
- Git

The `nlohmann/json` library is fetched automatically by CMake.

---

## Build & Run

### Linux / macOS

```bash
git clone https://github.com/Shubhtistic/CPP_Projects
cd CPP_Projects/todo_app

mkdir build && cd build
cmake ..
make todo_app

./todo_app
```

### Windows (PowerShell)

```bash
git clone https://github.com/Shubhtistic/CPP_Projects
cd CPP_Projects\todo_app

mkdir build && cd build
cmake ..
cmake --build .

.\Debug\todo_app.exe   # MSVC
.\todo_app.exe         # MinGW
```

---

## Data Persistence

`tasks.json` is created inside the build directory. It is saved automatically on exit and loaded on the next run.