# High-Performance C++ Log Query Engine 📈

## 📝 Summary
This is a high-performance, interactive command-line application for analyzing text-based log files. Modeled after real-world DevOps and SRE tools like Splunk or LogQL, this project is not just a static report generator; it is a full in-memory query engine.

The application loads an entire log file, parses it using a flexible, multi-format parsing system, and then provides the user with an interactive prompt (REPL) to run SQL-like queries against the data. The core of the project is a data processing engine built entirely on modern C++ STL algorithms and lambdas for maximum performance and expressiveness.

---

## ✨ Key Features
- **Interactive Query Loop (REPL):** After loading a file, the user gets an interactive prompt to run multiple queries without restarting the program.
- **Powerful Query Language:** Supports a simple yet powerful query syntax for data exploration:
    - **`COUNT`**: Counts log entries, with an optional `WHERE` clause.
    - **`LIST`**: Displays specific fields from log entries that match a `WHERE` clause.
    - **`TOP N`**: Finds the top N most frequent values for a given field (e.g., top 5 IP addresses).
- **Multi-Format Parsing:** Utilizes a polymorphic design (the Strategy Pattern) to support different log formats. The user can select the correct parser (e.g., "Simple Format" or "Apache Common Log Format") when loading a file.
- **Time-Based Filtering:** The `WHERE` clause supports time-based comparisons (e.g., `timestamp > "..."`), allowing for powerful time-series analysis.
- **Robust Input Handling:** The query parser is case-insensitive for field and value names, providing a more user-friendly experience.

---

## 🛠️ Core Concepts & Architecture
This project was architected to be a deep dive into advanced, modern C++ for high-performance data processing.

- **High-Performance Data Processing (STL & Lambdas):**
  - The project's **primary mandate** is to execute all query logic using the **C++ Standard Template Library**.
  - All counting and filtering operations are implemented with advanced algorithms like **`std::count_if`** and **`std::copy_if`**, powered by custom **lambda expressions** that translate the user's query into C++ logic.
  - Sorting for the `TOP N` query is handled by **`std::sort`** with a custom comparison lambda.

- **OOP & The Strategy Design Pattern:**
  - A polymorphic `LogParser` interface defines a contract for all parsers.
  - Concrete classes like `SimpleAppLogParser` and `ApacheLogParser` inherit from this interface, each providing its own specialized `std::regex` and parsing logic.
  - **`std::unique_ptr`** is used to correctly manage the lifetime of these polymorphic parser objects.

- **Robust Data Handling & Parsing:**
  - **`std::regex`**: The core of each parser, used to efficiently dissect and validate raw log lines based on complex patterns.
  - **`<chrono>` Library**: Timestamps are not stored as simple strings. They are parsed into `std::chrono::system_clock::time_point` objects, allowing for correct and efficient date/time comparisons in queries.
  - **`<filesystem>` Library**: User-provided file paths are handled using `std::filesystem::path`, making the application cross-platform (Windows, macOS, Linux).
  - **Case-Insensitive Processing**: User query strings are normalized to lowercase using **`std::transform`** to ensure robust matching.

- **Professional C++ Practices**:
  - **Clean Architecture:** A clear separation of concerns between components: `LogParser` (parsing), `LogStore` (storage), `QueryEngine` (analysis), and `Application` (UI/control).
  - **Modern C++17:** The project consistently uses modern features like `std::optional` for safe return types that may or may not contain a value.
  - **Build System:** A clean, professional `CMakeLists.txt` file manages the build process and dependencies.

---

## 💻 Tech Stack
- **C++17**
- **Standard Library:** STL algorithms, `<chrono>`, `<regex>`, `<filesystem>`, `<optional>`, `<unordered_map>`, etc.
- **Build System:** CMake

---

## ❓ Query Language Examples
The engine supports the following commands at its interactive prompt:

- **Count logs by level:**
    COUNT WHERE level = ERROR
- **List the messages of all warnings:**
    LIST message WHERE level = WARN

- **Find the top 5 most active IP addresses:**
    TOP 5 ip_address

- **List all logs after a specific time:**
    LIST  WHERE timestamp > "2025-10-17 14:00:00"
---
## 🚀 Getting Started

### Prerequisites
- A C++17 compliant compiler (GCC, Clang, MSVC)
- CMake (version 3.14 or higher)

### Installation & Setup
1.  **Clone the repository:**
  ```bash
  git clone git@github.com:Shubhtistic/CPP_Projects.git
  cd C++_Projects/log_query_engine
  ```
2.  **Create a build directory and compile:**
  ```bash
  mkdir build && cd build
  cmake ..
  make
  # to specifically make log_query_engine
  make log_query_engine
  ```

---
## 🎬 Usage

The application is run without any initial arguments and provides an interactive menu.

 - **Run the application (from the `build` directory):**
    ```bash
    # On Linux/macOS
    ./log_query_engine

    # On Windows
    .\log_query_engine.exe
    ```
- From the main menu, select **"Load a New Log File"**.
-  When prompted, enter the full path to the log file you wish to analyze.
-  Select the appropriate parser for your log file format from the menu.
- Once the file is loaded, select **"Analyze Loaded Data"** to enter the interactive query prompt.
