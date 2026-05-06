# C++ Log Query Engine

An interactive command-line application for analyzing text-based log files. Modeled after tools like Splunk and LogQL, it loads a log file into memory, parses it, and exposes an interactive query prompt (REPL) to run SQL-like queries against the data.

All query logic is built on STL algorithms and lambdas.

---

## Features

- **Interactive Query Loop (REPL)** — Load a file once, run multiple queries without restarting
- **Query Language** — Supports `COUNT`, `LIST`, and `TOP N` with optional `WHERE` clauses
- **Time-Based Filtering** — `WHERE` supports timestamp comparisons for time-series analysis
- **Multi-Format Parsing** — Polymorphic parser design supports multiple log formats; user selects the correct parser on load
- **Case-Insensitive Queries** — Field and value names are normalized automatically

---

## Query Language
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
---

## Core Concepts

**Data Processing**
- All filtering and counting uses STL algorithms: `std::count_if`, `std::copy_if`, `std::sort`
- Lambda expressions translate parsed query conditions into C++ logic at runtime

**Parser Architecture (Strategy Pattern)**
- `log_parser` is a polymorphic interface; concrete parsers (`simple_log_parser`, `apache_log_parser`, `nginx_log_parser`) each provide their own regex and parsing logic
- `std::unique_ptr` manages parser object lifetimes

**Data Handling**
- Timestamps parsed into `std::chrono::system_clock::time_point` for correct date/time comparisons
- File paths handled via `std::filesystem::path` for cross-platform compatibility, including `~` expansion
- `std::optional` used for safe return types where values may be absent

**Architecture**
- Clear separation of concerns: `log_parser` (parsing), `log_vector` (storage), `log_query` (analysis), `log_parse_app` (UI/control)
- CMake build system

---

## Parsers

### Simple Log Parser
- **Format:** `[YYYY-MM-DD HH:MM:SS] LEVEL - Message [- IP: x.x.x.x]`
- Expects exact timestamp format `YYYY-MM-DD HH:MM:SS` — will fail on any variation
- Optional IP address must be suffixed as ` - IP: ` at end of line

### Apache Log Parser
- **Format:** Apache Combined Log Format
- Example: `127.0.0.1 - - [10/Oct/2025:13:55:36 +0000] "GET /home.html HTTP/1.0" 200 2326`
- Handles escaped quotes (`\"`) in the request field
- Custom timestamp parser handles the non-standard Apache date format and timezone
- Will fail on Apache Common format (no referrer/user-agent) and Apache Error Log format

### Nginx Log Parser
- **Format:** Nginx Combined Log Format (identical to Apache Combined by default)
- Reuses the Apache parser's regex and timestamp logic
- Will fail if the server uses a custom `log_format` directive

---

## Prerequisites

- C++17 compiler (GCC / Clang / MSVC)
- CMake 3.14+
- Git

---

## Build & Run

```bash
git clone https://github.com/Shubhtistic/CPP_Projects.git
cd CPP_Projects/log_query_engine

mkdir build && cd build
cmake ..
make log_query_engine
```

```bash
# Linux / macOS
./log_query_engine

# Windows
.\log_query_engine.exe
```

On launch, select **"Load a New Log File"**, provide the file path, select the matching parser, then select **"Analyze Loaded Data"** to enter the query prompt.