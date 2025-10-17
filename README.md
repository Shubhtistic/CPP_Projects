

## 👋 Introduction

Welcome! I am a passionate software developer with a focus on building robust, high-performance backend systems and trying to explore the world of ML.

This repository is a **monorepo** that serves as a showcase for my foundational C++ projects. It is designed to demonstrate a progressive journey, starting from core software architecture principles and moving towards more advanced topics like object-oriented design, data structures, and concurrency.

My larger, "flagship" projects (such as my planned "Redis from Scratch" implementation) are housed in their own dedicated repositories.

---

## 📂 Project Index

| Project                                                                                              | Details                                                                                                                                                                    |
| ---------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 🕷️ **[High-Performance Web Crawler]** | _(Planned)_ A complex systems project integrating networking with advanced concurrency via a custom **Thread Pool** (`std::mutex`, `std::condition_variable`).                     |
| 🔑 **[Key-Value Store]** | _(Planned)_ A backend-focused in-memory database using efficient data structures (`std::unordered_map`) and modern C++ features like **`std::optional`** for clean API design. |
| 📊 **[Log File Analyzer](https://github.com/Shubhtistic/CPP_Projects/tree/main/log_file_analyzer)** | A high-performance utility applying advanced **STL Algorithms**, **Lambdas**, and efficient **String Parsing** for data aggregation.                                |
| 📈 **[Financial Trading Simulation](https://github.com/shubh4m-2k04/CPP_Projects/tree/main/financial_trade_simulation)** | A simulation demonstrating advanced **OOP** concepts, including **Polymorphism**, **Abstract Classes**, and modern memory management with **Smart Pointers**.                    |
| ✅ **[To-Do List Application](https://github.com/shubh4m-2k04/CPP_Projects/tree/main/todo_app)** | A robust application demonstrating fundamentals in **File I/O**, **JSON Data Persistence**, **RAII**, and professional project structure with **CMake**.                      |



## ⚙️ Prerequisites
Please make sure you already have:
- **C++17 compiler** (GCC/Clang/MSVC)
- **CMake** (v3.14+)
- **Git**

## 🚀 How to Build

**This is a monorepo managed by CMake. You can build all projects at once, or a specific project by its target name.**

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/Shubhtistic/CPP_Projects
    cd C++_Projects
    ```
2.  **Configure and Build:**
    ```bash
    mkdir build
    cd build
    cmake ..
    make # This will build ALL projects
    ```
3.  **To build only a specific project (e.g., the To-Do app):**
    ```bash
    # From inside the 'build' directory
    make todo_app
    ```
