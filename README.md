# 2x2x2 Rubik's Cube Solver

A modular, high-performance C++ implementation of a Pocket Rubik's Cube ($2 \times 2 \times 2$) solver utilizing advanced graph search and pathfinding algorithms. This project showcases the difference between brute-force search strategies and intelligent, heuristic-driven informed searches.

## 🚀 Key Features

* **Optimized State Representation:** The cube state is mapped cleanly as a 24-character array string, minimizing memory footprint during structural mutations.
* **Zero-Copy Path Reconstruction:** Utilizes a reversed parent tracking lookup map (`std::unordered_map`) in the A* engine to completely eliminate vector-copying overhead inside queue allocations.
* **Admissible Heuristic Bounds:** Features a mathematically sound misplaced-stickers lower-bound function that ensures optimal path lengths.
* **Integrated Pseudo-Random Scrambler:** Features a high-quality `<random>` uniform move generator that intelligently prevents immediate face backtracking.

---

## 🛠️ Implemented Search Strategies

| Algorithm | Strategy Type | Space Complexity | Guarantees Shortest Path? | Performance on Deep Scrambles |
| :--- | :--- | :--- | :--- | :--- |
| **BFS** | Brute-Force / Uninformed | $O(b^d)$ | **Yes** | 🛑 Memory Thrashing / High Latency |
| **DFS** | Brute-Force / Uninformed | $O(d)$ | No | 🛑 Trapped in Local Deep Cycles |
| **A\*** | Informed Search | $O(b^d)$ | **Yes** (with admissible $h(n)$) | ⚡ Fast (Zero-Copy Optimizations) |
| **IDA\*** | Iterative Deepening | $O(d)$ | **Yes** | ⚡ Extremely Fast & Light (Optimal) |

---

## 📂 Project Architecture

```text
rubiks_cube_solver/
├── CMakeLists.txt      # Build compilation settings
├── README.md           # Documentation
├── .gitignore          # Excludes build caches from Git tracking
├── Include/
│   ├── Cube.hpp        # Core state layouts, moves, and heuristic bounds
│   └── Solvers.hpp     # Graph traversal declarations
└── Src/
    ├── Cube.cpp        # Rotation mechanics & random scrambler
    ├── Solvers.cpp     # A* and IDA* core implementation mechanics
    └── main.cpp        # Demonstration pipeline wrapper entry-point
