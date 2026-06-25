#include <random>
#include "Cube.hpp"
#include <stdexcept>

const std::string SOLVED_STATE = "UUUUDDDDFFFFBBBBLLLLRRRR";

const std::unordered_map<char, std::vector<int>> MOVES = {
    {'U', {2, 0, 3, 1, 4, 5, 6, 7, 16, 17, 10, 11, 12, 13, 22, 23, 14, 15, 18, 19, 8, 9, 20, 21}},
    {'R', {0, 9, 2, 11, 4, 13, 6, 15, 8, 5, 10, 7, 12, 1, 14, 3, 16, 17, 18, 19, 20, 21, 23, 22}},
    {'F', {0, 1, 19, 17, 8, 9, 6, 7, 2, 3, 10, 11, 14, 12, 15, 13, 16, 5, 18, 4, 20, 21, 22, 23}}
};

std::string applyMove(const std::string& state, char move) {
    auto it = MOVES.find(move);
    if (it == MOVES.end()) {
        throw std::invalid_argument("Invalid move token applied.");
    }
    const auto& perm = it->second;
    std::string nextState = state;
    for (size_t i = 0; i < 24; ++i) {
        nextState[i] = state[perm[i]];
    }
    return nextState;
}

std::vector<std::pair<std::string, char>> getNeighbors(const std::string& state) {
    std::vector<std::pair<std::string, char>> neighbors;
    neighbors.reserve(MOVES.size());
    for (const auto& pair : MOVES) {
        neighbors.push_back({applyMove(state, pair.first), pair.first});
    }
    return neighbors;
}

double getHeuristic(const std::string& state) {
    int misplaced = 0;
    for (size_t i = 0; i < 24; ++i) {
        if (state[i] != SOLVED_STATE[i]) {
            misplaced++;
        }
    }
    return misplaced / 8.0;
}

std::vector<char> generateScramble(int length) {
    std::vector<char> availableMoves = {'U', 'R', 'F'};
    std::vector<char> scramble;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, availableMoves.size() - 1);
    
    char lastMove = '\0';
    while (scramble.size() < static_cast<size_t>(length)) {
        char move = availableMoves[distr(gen)];
        
        if (move != lastMove) {
            scramble.push_back(move);
            lastMove = move;
        }
    }
    return scramble;
}