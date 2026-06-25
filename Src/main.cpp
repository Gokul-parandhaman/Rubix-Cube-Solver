#include <iostream>
#include "Cube.hpp"
#include "Solvers.hpp"

void printSequence(const std::string& name, const std::vector<char>& path) {
    std::cout << name << ": [";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i] << (i == path.size() - 1 ? "" : ", ");
    }
    std::cout << "]\n";
}

int main() {
    std::cout << "Initializing C++ 3x3x3 Rubik's Cube Solver Pipeline...\n";
    std::cout << "Solved State Profile: " << SOLVED_STATE << "\n\n";

    int scrambleLength = 3; 
    std::vector<char> randomScramble = generateScramble(scrambleLength);
    printSequence("Generated Random Scramble", randomScramble);

    std::string scrambled = SOLVED_STATE;
    for (char move : randomScramble) {
        scrambled = applyMove(scrambled, move);
    }
    std::cout << "Scrambled State configuration: " << scrambled << "\n\n";

    std::cout << "Executing Search Implementations...\n";
    
    printSequence("BFS Solution  ", solveBFS(scrambled));
    
    printSequence("A* Solution   ", solveAStar(scrambled));
    
    printSequence("DFS Solution  ", solveDFS(scrambled, 3));

    return 0;
}