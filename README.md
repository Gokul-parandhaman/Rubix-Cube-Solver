# 3x3x3 Rubik's Cube Solver

A C++ implementation of a standard Rubik's Cube ($3 \times 3 \times 3$) solver utilizing advanced graph search and pathfinding algorithms. This project showcases the difference between brute-force search strategies and intelligent, heuristic-driven informed searches on a massive combinatorial state space.

## Key Features

* **Optimized State Representation:** The cube state is mapped cleanly as a 54-character string array representing the complete spatial layout of all six faces (U, D, F, B, L, R), minimizing memory footprints during structural permutations.
* **Lossless Permutation Matrices:** Utilizes fixed index translation vectors to mathematically simulate realistic 90-degree face rotations without facelet drift or color mutation.
* **Zero-Copy Path Reconstruction:** Utilizes a parent tracking lookup map (`std::unordered_map`) in the graph search engines to completely eliminate costly vector-copying overhead inside search queues.
* **Admissible Heuristic Bounds:** Features a relaxed misplaced-facelets lower-bound estimation function ($h(n) = \text{misplaced} / 12.0$) that guides informed searches safely toward the target configuration.
* **Integrated Pseudo-Random Scrambler:** Features a high-quality `<random>` uniform 6-axis move generator that intelligently prevents immediate face backtracking.

---

## Implemented Search Strategies

| Algorithm | Strategy Type | Space Complexity | Guarantees Shortest Path? | Performance on Deep Scrambles |
| :--- | :--- | :--- | :--- | :--- |
| **BFS** | Brute-Force / Uninformed | $O(b^d)$ | **Yes** | Optimal for short paths; highly memory-intensive |
| **DFS** | Brute-Force / Uninformed | $O(d)$ | No | Memory-light; requires depth guards to prevent infinite loops |
| **A\*** | Informed Search | $O(b^d)$ | **Yes** (with admissible $h(n)$) | Extremely fast for shallow states due to sharp node filtering |
| **IDA\*** | Iterative Deepening | $O(d)$ | **Yes** | Balanced memory footprints with optimal path guarantees |
