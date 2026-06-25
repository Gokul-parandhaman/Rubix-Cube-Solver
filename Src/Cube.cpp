#include <random>
#include "Cube.hpp"
#include <stdexcept>

const std::string SOLVED_STATE = "UUUUUUUUUDDDDDDDDDFFFFFFFFFBBBBBBBBBLLLLLLLLLRRRRRRRRR";

const std::unordered_map<char, std::vector<int>> MOVES = {
    {'U', {
        6, 3, 0, 7, 4, 1, 8, 5, 2,
        9, 10, 11, 12, 13, 14, 15, 16, 17,
        45, 46, 47, 21, 22, 23, 24, 25, 26,
        38, 41, 44, 30, 31, 32, 33, 34, 35,
        18, 19, 20, 39, 40, 41, 42, 43, 27,
        36, 29, 28, 48, 49, 50, 51, 52, 53
    }},
    {'D', {
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        15, 12, 9, 16, 13, 10, 17, 14, 11,
        42, 43, 44, 21, 22, 23, 24, 25, 26,
        47, 50, 53, 30, 31, 32, 33, 34, 35,
        27, 28, 29, 39, 40, 18, 42, 43, 19,
        20, 49, 46, 48, 49, 50, 51, 52, 36
    }},
    {'F', {
        0, 1, 2, 3, 4, 5, 44, 43, 42,
        20, 19, 18, 12, 13, 14, 15, 16, 17,
        24, 21, 18, 25, 22, 19, 26, 23, 20,
        27, 28, 29, 30, 31, 32, 33, 34, 35,
        36, 37, 9, 39, 40, 10, 41, 43, 11,
        6, 46, 47, 7, 49, 50, 8, 52, 53
    }},
    {'B', {
        51, 52, 53, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 38, 37, 36,
        18, 19, 20, 21, 22, 23, 24, 25, 26,
        33, 30, 27, 34, 31, 28, 35, 32, 29,
        2, 39, 40, 1, 40, 41, 0, 43, 44,
        45, 46, 17, 48, 49, 16, 50, 51, 15
    }},
    {'L', {
        35, 1, 2, 32, 4, 5, 29, 7, 8,
        18, 10, 11, 21, 13, 14, 24, 16, 17,
        9, 22, 23, 12, 22, 23, 15, 25, 26,
        27, 28, 6, 30, 31, 3, 33, 34, 0,
        42, 39, 36, 43, 40, 37, 44, 41, 38,
        45, 46, 47, 48, 49, 50, 51, 52, 53
    }},
    {'R', {
        0, 1, 26, 3, 4, 23, 6, 7, 20,
        9, 10, 35, 12, 13, 32, 14, 15, 29,
        18, 19, 11, 21, 22, 14, 24, 25, 17,
        27, 28, 2, 30, 31, 5, 33, 34, 8,
        36, 37, 38, 39, 40, 41, 42, 43, 44,
        51, 48, 45, 52, 49, 46, 53, 50, 47
    }}
};

std::string applyMove(const std::string& state, char move) {
    auto it = MOVES.find(move);
    if (it == MOVES.end()) {
        throw std::invalid_argument("Invalid move token applied.");
    }
    const auto& perm = it->second;
    std::string nextState = state;
    for (size_t i = 0; i < 54; ++i) {
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
    for (size_t i = 0; i < 54; ++i) {
        if (state[i] != SOLVED_STATE[i]) {
            misplaced++;
        }
    }
    return misplaced / 12.0;
}

std::vector<char> generateScramble(int length) {
    std::vector<char> availableMoves = {'U', 'D', 'F', 'B', 'L', 'R'};
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