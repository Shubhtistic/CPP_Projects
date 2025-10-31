Okay, understood. I will not change any of the existing content you provided. I will create a new, detailed section about the parsers and their specific logic and limitations, and I will insert it strategically into the `README.md`.

Here is the complete, updated `README.md` file in a single Markdown block.

````markdown
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
  - A polymorphic `log_parser` interface defines a contract for all parsers.
  - Concrete classes like `simple_log_parser`, `apache_log_parser`, and `nginx_log_parser` inherit from this interface, each providing its own specialized `std::regex` and parsing logic.
  - **`std::unique_ptr`** is used to correctly manage the lifetime of these polymorphic parser objects in the `Application`'s "toolbox" vector.

- **Robust Data Handling & Parsing:**
  - **`std::regex`**: The core of each parser, used to efficiently dissect and validate raw log lines based on complex patterns.
  - **`<chrono>` Library**: Timestamps are not stored as simple strings. They are parsed into `std::chrono::system_clock::time_point` objects, allowing for correct and efficient date/time comparisons in queries.
  - **`<filesystem>` Library**: User-provided file paths are handled using `std::filesystem::path`, making the application cross-platform (Windows, macOS, Linux) and capable of expanding `~` to the home directory.
  - **Case-Insensitive Processing**: User query strings are normalized for case to ensure robust matching.

- **Professional C++ Practices**:
  - **Clean Architecture:** A clear separation of concerns between components: `log_parser` (parsing), `log_vector` (storage), `log_query` (analysis), and `log_parse_app` (UI/control).
  - **Modern C++17:** The project consistently uses modern features like `std::optional` for safe return types that may or may not contain a value.
  - **Build System:** A clean, professional `CMakeLists.txt` file manages the build process and dependencies.

---

## 🔬 The Parsers: A Deep Dive

This engine's flexibility comes from its modular parser architecture (the Strategy Pattern). Each parser is a specialized "key" designed for a specific "lock" (log format). The engine loads all available parsers and asks the user to select the correct one for their file.

### 1. Simple Log Parser
* **Name:** `Simple Log parser`
* **Format:** `[YYYY-MM-DD HH:MM:SS] LEVEL - Message [- IP: x.x.x.x]`
* **Purpose:** This parser is designed for a common custom application log format. It expects a standard, sortable timestamp, a log level, and a message. It can also optionally extract an IP address if it's at the end of the line.
* **Edge Cases & Limitations:**
    * **Strict Timestamp:** The parser will **fail** if the timestamp is not in the exact `YYYY-MM-DD HH:MM:SS` format.
    * **Strict IP Format:** The optional IP address **must** be prefixed with ` - IP: ` at the end of the line, or it will be missed.

### 2. Apache Log Parser
* **Name:** `Apache Log Parser`
* **Format:** The "Apache Combined Log Format."
    * *Example:* `127.0.0.1 - - [10/Oct/2025:13:55:36 +0000] "GET /home.html HTTP/1.0" 200 2326`
* **Purpose:** This is a high-performance, robust parser for one of the most common web server log formats in the world.
* **Key Features:**
    * **Robust Regex:** Uses a professional-grade regex (`R"(^([\d.]+|[\da-fA-F:]+)\s+(\S+)\s+(\S+)\s+\[(.*?)\]\s+"((?:\\.|[^"\\])*)"...)"`) that can correctly handle edge cases like escaped quotes (`\"`) in the request field.
    * **Custom Timestamp Parser:** Includes a dedicated helper function that manually parses the non-standard Apache timestamp (`DD/Mon/YYYY...`) by mapping month names (`Oct`) to numbers and handling timezones (`%z`) for correct conversion to a `time_point`.
* **Edge Cases & Limitations:**
    * This parser is **specialized**. It will **correctly fail** if given a log file in the simpler "Apache Common" format (which omits the referrer and user-agent).
    * It will also **correctly fail** if given an "Apache Error Log" file, which has a completely different format.

### 3. Nginx Log Parser
* **Name:** `Nginx Log Parser`
* **Format:** The "Nginx Combined Log Format."
    * *Example:* `54.36.149.41 - - [22/Jan/2019:03:56:14 +0330] "GET /filter/..." 200 30577 ...`
* **Purpose:** Demonstrates reusing logic, as the default Nginx format is identical to the Apache Combined format.
* **Key Features:**
    * Reuses the exact same robust regex and timestamp parsing logic from the `ApacheLogParser`, demonstrating good code design.
* **Edge Cases & Limitations:**
    * This parser will **only** work for the default Nginx configuration. It will **fail** if the server uses a *custom* `log_format` directive, which is very common in professional environments.

---

## 💻 Tech Stack
- **C++17**
- **Standard Library:** STL algorithms, `<chrono>`, `<regex>`, `<filesystem>`, `<optional>`, `<unordered_map>`, etc.
- **Build System:** CMake

---

## ❓ Query Language Examples
The engine supports the following commands at its interactive prompt:

- **Count logs by level:**
    ```
    > COUNT WHERE level = ERROR
    ```
- **List the messages of all warnings:**
    ```
    > LIST message WHERE level = WARN
    ```
- **Find the top 5 most active IP addresses:**
    ```
    > TOP 5 ip_address
    ```
- **List all logs after a specific time:**
    ```
    > LIST * WHERE timestamp > "2025-10-17 14:00:00"
    ```
---
## 🚀 Getting Started

### Prerequisites
- A C++17 compliant compiler (GCC, Clang, MSVC)
- CMake (version 3.14 or higher)
- Git

### Installation & Setup
1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/Shubhtistic/CPP_Projects.git](https://github.com/Shubhtistic/CPP_Projects.git)
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

1.  **Run the application (from the `build` directory):**
    ```bash
    # On Linux/macOS
    ./log_query_engine

    # On Windows
    .\log_query_engine.exe
    ```
2.  From the main menu, select **"Load a New Log File"**.
3.  When prompted, enter the full path to the log file you wish to analyze (e.g., `~/Downloads/apache.log`).
4.  Select the appropriate parser for your log file format from the menu.
5.  Once the file is loaded, select **"Analyze Loaded Data"** to enter the interactive query prompt.
````