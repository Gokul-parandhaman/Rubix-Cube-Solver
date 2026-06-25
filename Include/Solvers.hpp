#ifndef SOLVERS_HPP
#define SOLVERS_HPP

#pragma once
#include <string>
#include <vector>

std::vector<char> solveBFS(const std::string& startState);
std::vector<char> solveDFS(const std::string& startState, int maxDepth = 7);
std::vector<char> solveAStar(const std::string& startState);
std::vector<char> solveIDAStar(const std::string& startState);

#endif 