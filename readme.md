
# 8-Puzzle Solver - A* Search Algorithm with Multiple Heuristics

## Overview
This program solves the classic 8-puzzle game using the A* search algorithm with five different heuristics:
1. **Manhattan Distance**
2. **Misplaced Tiles**
3. **Pattern Database (simplified)**
4. **Linear Conflict**
5. **Weighted Manhattan Distance**

The program compares the effectiveness and efficiency of these heuristics in finding the optimal solution from various initial states to the goal state.

---

## Prerequisites
To compile and run this program, you need:
- A C++ compiler that supports **C++11** or higher (e.g., GCC, Clang, MSVC)
- A command-line interface:
  - Terminal (macOS/Linux)
  - Command Prompt or PowerShell (Windows)

---

## Files Included
- `Project2-hme36.cpp` - The main program file containing the core logic.
- `heuristic1.h` - Implementation of Heuristic 1 (Manhattan Distance).
- `heuristic2.h` - Implementation of Heuristic 2 (Misplaced Tiles).
- `heuristic3.h` - Implementation of Heuristic 3 (Pattern Database).
- `heuristic4.h` - Implementation of Heuristic 4 (Linear Conflict).
- `heuristic5.h` - Implementation of Heuristic 5 (Weighted Manhattan Distance).
- `constants.h` - Contains shared constants like the goal state.

Ensure all files are in the same directory.

---

## Instructions

### 1. Download the Files
Place all the listed files into a single directory on your computer.

### 2. Open a Command-Line Interface
- **Windows:** Open Command Prompt or PowerShell.
- **macOS/Linux:** Open Terminal.

Navigate to the directory containing the program files using the `cd` command:
```bash
cd path/to/your/directory
```

### 3. Compile the Program
Use the following command to compile the program:

- For GCC or Clang:
  ```bash
  g++ Project2-hme36.cpp -o puzzle_solver
  ```

- For MSVC (Microsoft Visual C++):
  ```bash
  cl Project2-hme36.cpp /Fe:puzzle_solver.exe
  ```

> **Note:** If using an IDE (e.g., Visual Studio, Code::Blocks, CLion), create a new project and add all the files to it before building.

### 4. Run the Program
After successful compilation, run the executable:

- **macOS/Linux:**
  ```bash
  ./puzzle_solver
  ```

- **Windows:**
  ```cmd
  puzzle_solver.exe
  ```

### 5. Program Output
The program will execute the A* search algorithm using each of the five heuristics on two initial puzzle states. The output includes:
- Path to the goal
- Solution cost (depth)
- Execution time
- Nodes generated
- Nodes expanded
- Effective branching factor
- Final state of the puzzle

### 6. Customizing Initial States (Optional)
You can modify the `initialState1` and `initialState2` variables in `main.cpp` to test different initial states.

1. Open `main.cpp` in a text editor or IDE.
2. Locate the initial state definitions:
    ```cpp
    vector<vector<int>> initialState1 = {
        {2, 8, 3},
        {1, 6, 4},
        {0, 7, 5}
    };

    vector<vector<int>> initialState2 = {
        {2, 1, 6},
        {4, 0, 8},
        {7, 5, 3}
    };
    ```
3. Modify these vectors to represent your desired initial states, ensuring:
   - The state is a 3x3 grid.
   - Tiles are numbered from 0 to 8 (0 represents the blank space).
   - No duplicate numbers exist.
   - The puzzle configuration is solvable.

4. Save your changes and recompile the program:
    ```bash
    g++ Project2-hme36.cpp -o puzzle_solver
    ```

5. Run the program again to see results with your custom initial states:
    ```bash
    ./puzzle_solver      # macOS/Linux
    puzzle_solver.exe    # Windows
    ```

---

## Troubleshooting

### Compiler Errors
1. **"No such file or directory"**:
   - Ensure all `.h` files are in the same directory as `Project2-hme36.cpp`.
   - Verify the filenames are correct.

2. **"Undefined reference" or "Linker errors"**:
   - Ensure all functions are defined properly in the header files.
   - Since all code is included in `Project2-hme36.cpp`, compiling this file should suffice.

3. **"Permission denied" (macOS/Linux)**:
   - Grant execute permissions to the compiled binary:
     ```bash
     chmod +x puzzle_solver
     ```

### Runtime Errors
1. **Program crashes or behaves unexpectedly**:
   - Verify the initial states are valid (numbers 0 to 8, no duplicates).
   - Ensure the initial state is solvable.

2. **No output or incomplete output**:
   - Wait for a few moments; complex initial states may take longer to compute.
   - Check if the program is paused or waiting for input.

## Tested Configurations
The program has been tested on the following:
- **Operating Systems**: Windows 10, macOS Catalina, Ubuntu 20.04
- **Compilers**: GCC 9.3.0, Clang 10.0.0, MSVC 2019

> Note: Compiler commands or settings may vary based on your system.
