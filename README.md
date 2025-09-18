

## 👋 Introduction

Welcome! I am a passionate software developer with a focus on building robust, high-performance backend systems and trying to explore the world of ML.

This repository is a **monorepo** that serves as a showcase for my foundational C++ projects. It is designed to demonstrate a progressive journey, starting from core software architecture principles and moving towards more advanced topics like object-oriented design, data structures, and concurrency.

My larger, "flagship" projects (such as my planned "Redis from Scratch" implementation) are housed in their own dedicated repositories.

---

## 📂 Project Index

| Project                                         | Details                                                                                  |
| ----------------------------------------------- | ---------------------------------------------------------------------------------------- |
| 🚀 **[To-Do List Application](https://github.com/shubh4m-2k04/CPP_Projects/tree/main/todo_app)**       | A robust, persistent command-line task manager showcasing **Separation of Concerns**, **RAII**, **JSON Serialization**, **CMake**, and **Robust Error Handling**. |
| 📈 **[Financial Trading Sim][trading-link]**     | _(Next Up)_ A simulation of a financial portfolio system demonstrating **Polymorphism**, **Inheritance**, **Virtual Functions**, **Smart Pointers**, and **Advanced OOP Design**. |
| 📊 **[Log File Analyzer][log-link]**             | _(Planned)_ A high-performance server log analysis tool applying **STL Algorithms**, **Lambdas**, **String Parsing**, and **Data Aggregation**. |
| 🕷️ **[Web Scraper][scraper-link]**              | _(Planned)_ A concurrent web crawler featuring **Multithreading** (`std::thread`, `std::mutex`), **Networking**, **HTML Parsing**, and **Concurrent Data Structures**. |

[trading-link]: ./financial-trading-sim
[log-link]: ./log-file-analyzer
[scraper-link]: ./web-scraper


## ⚙️ Prerequisites
Please make sure you already have:
- **C++17 compiler** (GCC/Clang/MSVC)
- **CMake** (v3.14+)
- **Git**

## 🚀 How to Build

**This is a monorepo managed by CMake. You can build all projects at once, or a specific project by its target name.**

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/shubh4m-2k04/CPP_Projects
    cd C++-Projects
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
