#ifndef CUBE_HPP
#define CUBE_HPP

#pragma once
#include <string>
#include <vector>
#include <unordered_map>

extern const std::string SOLVED_STATE;

extern const std::unordered_map<char, std::vector<int>> MOVES;

std::string applyMove(const std::string& state, char move);

std::vector<std::pair<std::string, char>> getNeighbors(const std::string& state);

double getHeuristic(const std::string& state);

std::vector<char> generateScramble(int length);

#endif