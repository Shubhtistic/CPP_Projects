# C++ Financial Trading Simulation

A command-line trading simulation built in modern C++. It models a dynamic financial market with multiple asset types, demonstrating advanced OOP, modern memory management, and a clean separation between application logic and data.

The market is fully data-driven — assets are loaded from an external CSV file at runtime, so the configuration can be changed without recompiling.

---

## Features

- **Data-Driven Market** — Tradable assets are loaded from `market_assets.csv` at startup, no hard-coded values
- **Polymorphic Asset System** — `Stock` and `Bond` types are managed through a common `Asset` interface
- **Dynamic Market Simulation** — A `TICK` command advances time, causing stock prices to fluctuate and bonds to accrue interest
- **Portfolio Management** — `BUY` and `SELL` commands update cash balance and holdings in real time
- **Robust Input Handling** — Uses a `getline` + `stringstream` pattern throughout to prevent input buffer errors

---

## Core Concepts

**Architecture**
- A top-level `Simulation` class encapsulates the full program lifecycle, keeping `main()` a clean entry point
- Clear separation between application logic (`Simulation`), component logic (`Portfolio`), and configuration data (CSV)

**OOP**
- Abstract `Asset` base class defines the interface; `Stock` and `Bond` provide specialized implementations
- All assets are accessed polymorphically via `Asset*` pointers
- Constructors enforce valid object state (RAII)

**Memory Management**
- `std::unique_ptr` owns all master asset objects in the `market` collection — automatic cleanup, no leaks
- `Portfolio` uses non-owning raw `Asset*` pointers as observers, demonstrating the ownership vs. usage distinction

**Data & STL**
- CSV parsed at runtime using `std::ifstream` and `std::stringstream`
- `std::map` used for portfolio holdings — O(log n) lookups
- `<random>` library used for market volatility simulation

**C++ Practices**
- `const`-correctness applied on member functions and parameters throughout
- Modular structure: `src/` for implementation, `include/` for headers
- CMake build system

---

## Prerequisites

- C++17 compiler (GCC / Clang / MSVC)
- CMake 3.10+
- Git

---

## Configuration

The market is configured via `market_assets.csv` in the project root. Expected format:

```csv
TYPE,SYMBOL,PRICE,INTEREST_RATE
Stock,GOOG,135.25,0
Bond,US-BOND,1000.0,0.05
```

---

## Build & Run

### Linux / macOS

```bash
git clone git@github.com:Shubhtistic/CPP_Projects.git
cd CPP_Projects/financial_trade_simulation

mkdir build && cd build
cmake ..
make

./TradingSim
```

### Windows (PowerShell)

```bash
git clone git@github.com:Shubhtistic/CPP_Projects.git
cd CPP_Projects\financial_trade_simulation

mkdir build && cd build
cmake ..
cmake --build .

.\Debug\TradingSim.exe
```