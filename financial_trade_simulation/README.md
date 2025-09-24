# C++ Financial Trading Simulation 📈

## 📝 Summary
This is a sophisticated command-line trading simulation built in modern C++. It models a dynamic financial market with multiple types of assets, demonstrating a deep understanding of advanced Object-Oriented Programming (OOP) principles, modern memory management, and professional C++ practices.

The core of this project is a powerful polymorphic design that allows different assets, like stocks and bonds, to be managed through a single, stable interface, showcasing how to build flexible and extensible systems.

---

## ✨ Key Features
- **Polymorphic Asset System**: The simulation seamlessly manages different asset types (`Stock`, `Bond`) with unique behaviors through a common `Asset` interface.
- **Dynamic Market Simulation**: A `TICK` command advances time, causing stock prices to fluctuate randomly and bonds to generate interest payments.
- **Full Portfolio Management**: Users can `BUY` and `SELL` assets, with all transactions affecting their cash balance and holdings.
- **Interactive Command-Line Interface**: All simulation actions are driven by a clean and simple text-based interface.
- **Efficient Data Structures**: Uses `std::map` for fast, efficient lookups of asset holdings within the user's portfolio.

---

## 🛠️ Core Concepts Demonstrated
This project was architected to be a deep dive into advanced C++ and software design principles.

- **Advanced Object-Oriented Programming (OOP)**:
  - **Polymorphism & Inheritance**: A master `Asset` class defines a contract, with `Stock` and `Bond` providing specialized, derived implementations. The `Portfolio` and main loop interact with all assets polymorphically via `Asset*` pointers.
  - **Abstract Classes & Pure Virtual Functions**: The `Asset` class is a true Abstract Base Class, which cannot be instantiated and enforces its contract on all derived classes using pure virtual functions.
  - **The `override` Keyword**: Used on all derived virtual functions to ensure compile-time safety and clearly express design intent.

- **Modern C++ Memory Management**:
  - **RAII & Smart Pointers (`std::unique_ptr`)**: The "market" collection owns all master asset objects using `std::unique_ptr`, guaranteeing automatic cleanup and preventing memory leaks.
  - **Non-Owning Raw Pointers**: The `Portfolio` correctly uses raw `Asset*` pointers as non-owning observers to reference assets owned by the market, demonstrating a key C++ design pattern for separating ownership from usage.

- **Standard Template Library (STL) Mastery**:
  - **`std::map`**: Used for the portfolio's holdings to provide efficient, key-based lookups of asset quantities.
  - **`std::vector`**: Used to hold the master list of market assets.
  - **`<random>` Library**: Employs the modern C++ random library (`std::mt19937`, `std::uniform_real_distribution`) for a high-quality simulation of market volatility.

- **Professional C++ Practices**:
  - **`const`-Correctness**: `const` is applied rigorously throughout the codebase on member functions and parameters to enforce read-only access and prevent unintended side effects.
  - **Modular, Header-Based Design**: The project is cleanly separated into logical components (`Asset`, `Stock`, `Bond`, `Portfolio`), each with its own header and source file.
  - **Clean Build System**: Uses a simple, professional `CMakeLists.txt` file for easy compilation on any platform.

---

## ⚙️ Prerequisites
Please make sure you have the following installed:
- A C++17 compliant compiler (GCC, Clang, MSVC)
- CMake (version 3.10 or higher)
- Git

---

## 💻 Installation & Setup

### 🔹 Linux & macOS

1.  **Clone the repository and navigate to the project folder:**
    ```bash
    git clone https://github.com/shubh4m-2k04/CPP_Projects
    cd C++-Projects/financial-sim
    ```
2.  **Create a build directory and compile:**
    ```bash
    mkdir build && cd build
    cmake ..
    make
    #or optinally
    make trading_sim
    # to only make the trading_sim executable only
    ```
3.  **Run the application:**
    ```bash
    ./trading_sim
    ```
    The executable file will be in build directory
Or in the folder you used for build

### 🔹 Windows (Using PowerShell)
1.  **Clone the repository and navigate to the project folder:**
    ```bash
    git clone https://github.com/shubh4m-2k04/CPP_Projects
    cd C++-Projects\financial-sim
    ```
2.  **Create a build directory and compile:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
3.  **Run the application:**
    ```bash
    .\Debug\trading_sim.exe
    ```

---

## 📂 Data Persistence

This is an **in-memory simulation**. The state of the market and the user's portfolio is **reset** every time the application is launched. No data is saved to disk.
