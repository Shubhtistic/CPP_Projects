# C++ Financial Trading Simulation 📈

## 📝 Summary
This is a sophisticated command-line trading simulation built in modern C++. It models a dynamic financial market with multiple types of assets, demonstrating a deep understanding of advanced Object-Oriented Programming (OOP), professional software architecture, and modern C++ practices.

The core of this project is a powerful polymorphic design that allows different assets to be managed through a single, stable interface. The application is fully data-driven, loading its market configuration from an external CSV file, showcasing a clean separation between logic and data.

---

## ✨ Key Features
- **Data-Driven Market**: The list of tradable assets is not hard-coded but loaded from an external `market_assets.csv` file, allowing for easy configuration without recompiling.
- **Polymorphic Asset System**: The simulation seamlessly manages different asset types (`Stock`, `Bond`) with unique behaviors through a common `Asset` interface.
- **Dynamic Market Simulation**: A `TICK` command advances time, causing stock prices to fluctuate randomly and bonds to generate interest payments.
- **Full Portfolio Management**: Users can `BUY` and `SELL` assets, with all transactions affecting their cash balance and holdings.
- **Robust Command-Line Interface**: All user input is handled safely using a `getline` and `stringstream` pattern, preventing common input buffer errors.

---

## 🛠️ Core Concepts Demonstrated
This project was architected to be a deep dive into advanced C++ and software design principles.

- **Software Architecture**:
  - **Encapsulation & Application Class**: A top-level `Simulation` class encapsulates the entire program lifecycle (setup, run loop, teardown), simplifying the `main()` function to a clean entry point.
  - **Separation of Concerns**: A clear distinction is maintained between application logic (`Simulation`), component logic (`Portfolio`), and configuration data (the external CSV file).

- **Advanced Object-Oriented Programming (OOP)**:
  - **Polymorphism & Inheritance**: An abstract `Asset` class defines a contract, with `Stock` and `Bond` providing specialized, derived implementations. The system interacts with all assets polymorphically via `Asset*` pointers.
  - **RAII & Class Invariants**: Constructors are used to guarantee that all objects (`Portfolio`, `Simulation`) are created in a valid and usable state.

- **Modern C++ Memory Management**:
  - **Smart Pointers (`std::unique_ptr`)**: The `market` collection owns all master asset objects using `std::unique_ptr`, guaranteeing automatic cleanup and preventing memory leaks.
  - **Non-Owning Raw Pointers**: The `Portfolio` correctly uses raw `Asset*` pointers as non-owning observers to reference assets, demonstrating a key design pattern for separating ownership from usage.

- **Data Handling & STL Mastery**:
  - **CSV File Parsing**: Uses `std::ifstream` and `std::stringstream` to read and parse the external market data file at runtime.
  - **`std::map`**: Used for the portfolio's holdings to provide efficient, O(log n) lookups of asset quantities.
  - **`<random>` Library**: Employs the modern C++ random library for a high-quality simulation of market volatility.

- **Professional C++ Practices**:
  - **Robust Input Handling**: Consistently uses a `getline` + `stringstream` pattern to create a reliable and crash-proof user interface.
  - **`const`-Correctness**: `const` is applied rigorously on member functions and parameters to enforce safety and express design intent.
  - **Modular Project Structure**: The project is cleanly separated into `src/` (implementation) and `include/` (header) directories.
  - **Build Automation**: Uses a professional `CMakeLists.txt` file for easy compilation on any platform.

---

## ⚙️ Prerequisites
Please make sure you have the following installed:
- A C++17 compliant compiler (GCC, Clang, MSVC)
- CMake (version 3.10 or higher)
- Git

---

## 💻 Installation & Setup
The project requires a `market_assets.csv` file in the root directory to define the tradable assets. An example is provided in the repository.

### 🔹 Linux & macOS

1.  **Clone the repository and navigate to the project folder:**
    ```bash
    git clone git@github.com:shubh4m-2k04/CPP_Projects.git
    cd C++_projects/financial_trade_simulation
    ```
2.  **Create a build directory and compile:**
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```
3.  **Run the application (from the `build` directory):**
    ```bash
    ./TradingSim
    ```

### 🔹 Windows (Using PowerShell)
1.  **Clone the repository and navigate to the project folder:**
    ```bash
    git clone <your-repo-url>
    cd <repo-folder>\financial-sim
    ```
2.  **Create a build directory and compile:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
3.  **Run the application (from the `build` directory):**
    ```bash
    .\Debug\TradingSim.exe
    ```

---

## ⚙️ Configuration
The market is configured via a `market_assets.csv` file located in the project's root directory. The application loads this file on startup. The expected format is:
```csv
TYPE,SYMBOL,PRICE,INTEREST_RATE
Stock,GOOG,135.25,0
Bond,US-BOND,1000.0,0.05