# C++ Projects

A monorepo showcasing foundational to intermediate C++ projects. The work here demonstrates a progressive focus on core software architecture, object-oriented design, data processing, and systems programming.

Larger standalone projects (such as a planned Redis implementation) are housed in their own dedicated repositories.

---

## Project Index

| Project | Details |
| --- | --- |
| **[Networked Key-Value Store](https://github.com/Shubhtistic/CPP_Projects/tree/main/networked_kv_store)** | _(In Progress)_ A backend-focused in-memory database using efficient data structures (`std::unordered_map`), server-side socket programming, and a custom network protocol. |
| **[Log Query Engine](https://github.com/Shubhtistic/CPP_Projects/tree/main/log_query_engine)** | An interactive CLI tool for analyzing log files with a SQL-like query language, built on STL algorithms, lambdas, regex, and a polymorphic parser design. |
| **[Financial Trading Simulation](https://github.com/shubh4m-2k04/CPP_Projects/tree/main/financial_trade_simulation)** | A simulation demonstrating advanced OOP — polymorphism, abstract classes, and modern memory management with smart pointers. |
| **[To-Do List Application](https://github.com/shubh4m-2k04/CPP_Projects/tree/main/todo_app)** | A CLI application covering File I/O, JSON persistence, RAII, and project structure with CMake. |

---

## Prerequisites

- C++17 compiler (GCC / Clang / MSVC)
- CMake 3.14+
- Git

---

## Building

This monorepo is managed by CMake and can be built in full or per project.

```bash
# Clone the repository
git clone https://github.com/Shubhtistic/CPP_Projects
cd CPP_Projects

# Configure and build all projects
mkdir build && cd build
cmake ..
make

# Build a specific project
make todo_app
```