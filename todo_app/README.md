
# C++ Command-Line To-Do List Application
A robust command-line to-do list app in modern C++ for efficient task management. Features a professional architecture with separation of concerns, robust error handling, and data persistence via a JSON file, auto-saved on exit and reloaded on startup.





## ✨ Key Features
- Full CRUD Functionality: Create, view, edit, and delete tasks.

- Persistent Storage: Task data is automatically serialized to tasks.json on exit and deserialized on launch.

- Task State Management: Mark tasks as "complete" or "pending" and filter the view to see only pending tasks.

- Robust Input Handling: The application is resilient to invalid user input, preventing crashes and providing clear error messages.

- Stable ID System: Each task is assigned a permanent, unique ID that remains stable even when other tasks are deleted.
## 🛠️ Core Concepts & Skills Demonstrated

Software Architecture:
- SoC: Two-tier design separates manager (logic) and console (UI) for reusability.
- RAII: Manager class auto-manages tasks.json loading/saving.

C++ & OOP:

- Design: Clear classes (manager, console, todo_data_type).
- Encapsulation: Private data, public functions.
- Overloading: Multiple add_task versions for user/file tasks.
- Modern C++: Uses STL, const correctness, header guards.

Data Handling:

- JSON: Tasks serialized/deserialized with nlohmann/json via CMake.
- Error Handling: Try-catch for file I/O and JSON errors.

Tooling:

- CMake: Modern build system.
- Git: Professional workflow with .gitignore.

## ⚙️ Prerequisites
To build and run this project, you will need the following installed on your system (Linux/macOS):

- A C++ Compiler: Such as g++.

- CMake: Version 3.10 or higher.

- Git: For cloning the repository.

The nlohmann/json library is handled automatically by CMake and does not need to be installed manually.

## 🛠️ Build & Run Instructions

- Clone the repository:

```bash
git clone https://github.com/shubh4m-2k04/Cpp-ToDo-list
````

---

#### 🐧 Linux & 🍎 macOS
- Create a build directory:

   ```bash
   mkdir build
   cd build
   ```

- Configure with CMake:

   ```bash
   cmake ..
   ```

- Compile:

   ```bash
   make
   ```

- Run:

   ```bash
   ./todo_app
   ```

   The `tasks.json` file will be created/updated in the `build` directory.

---

#### 🏁 Windows

- Create a build directory:

   ```powershell
   mkdir build
   cd build
   ```

- Configure with CMake:

   ```powershell
   cmake ..
   ```

- Compile (choose one):

   * **Command Line**:

     ```powershell
     cmake --build .
     ```

   * **Visual Studio GUI**:

     * Open the generated `.sln` file in the `build` folder.
     * Set `todo_app` as the Startup Project.
     * Build the solution (F7 or Build > Build Solution).

- Run:

   ```powershell
   .\Debug\todo_app.exe
   ```

   The `tasks.json` file will be created/updated in the `build\Debug` directory.

