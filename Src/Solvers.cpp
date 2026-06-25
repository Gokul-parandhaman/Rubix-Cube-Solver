#include "Solvers.hpp"
#include "Cube.hpp"
#include <queue>
#include <unordered_set>
#include <limits>
#include <algorithm>

std::vector<char> solveBFS(const std::string& startState) {
    if (startState == SOLVED_STATE) return {};

    std::queue<std::pair<std::string, std::vector<char>>> q;
    std::unordered_set<std::string> visited;

    q.push({startState, {}});
    visited.insert(startState);

    while (!q.empty()) {
        auto [current, path] = q.front();
        q.pop();

        for (const auto& [nextState, move] : getNeighbors(current)) {
            std::vector<char> nextPath = path;
            nextPath.push_back(move);

            if (nextState == SOLVED_STATE) return nextPath;

            if (visited.find(nextState) == visited.end()) {
                visited.insert(nextState);
                q.push({nextState, nextPath});
            }
        }
    }
    return {};
}

bool dfsHelper(const std::string& state, int depth, int maxDepth, 
               std::vector<char>& path, std::unordered_set<std::string>& visited) {
    if (state == SOLVED_STATE) return true;
    if (depth >= maxDepth) return false;

    for (const auto& [nextState, move] : getNeighbors(state)) {
        if (visited.find(nextState) == visited.end()) {
            visited.insert(nextState);
            path.push_back(move);

            if (dfsHelper(nextState, depth + 1, maxDepth, path, visited)) return true;

            path.pop_back();
            visited.erase(nextState);
        }
    }
    return false;
}

std::vector<char> solveDFS(const std::string& startState, int maxDepth) {
    std::vector<char> path;
    std::unordered_set<std::string> visited = {startState};
    if (dfsHelper(startState, 0, maxDepth, path, visited)) return path;
    return {};
}

struct AStarNode {
    double fScore;
    std::string state;
    std::vector<char> path;

    bool operator>(const AStarNode& other) const {
        return fScore > other.fScore;
    }
};

std::vector<char> solveAStar(const std::string& startState) {
    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;
    std::unordered_map<std::string, int> gScore;

    openSet.push({getHeuristic(startState), startState, {}});
    gScore[startState] = 0;

    while (!openSet.empty()) {
        auto [f, current, path] = openSet.top();
        openSet.pop();

        if (current == SOLVED_STATE) return path;

        int currentG = gScore[current];

        for (const auto& [nextState, move] : getNeighbors(current)) {
            int tentativeG = currentG + 1;

            if (gScore.find(nextState) == gScore.end() || tentativeG < gScore[nextState]) {
                gScore[nextState] = tentativeG;
                double nextF = tentativeG + getHeuristic(nextState);
                
                std::vector<char> nextPath = path;
                nextPath.push_back(move);
                
                openSet.push({nextF, nextState, nextPath});
            }
        }
    }
    return {};
}

double idastarSearch(std::vector<std::string>& path, std::vector<char>& pathMoves, 
                     int g, double bound, std::unordered_set<std::string>& visited) {
    const std::string& state = path.back();
    double f = g + getHeuristic(state);
    if (f > bound) return f;
    if (state == SOLVED_STATE) return -1.0; 

    double minBound = std::numeric_limits<double>::infinity();

    for (const auto& [nextState, move] : getNeighbors(state)) {
        if (visited.find(nextState) == visited.end()) {
            visited.insert(nextState);
            path.push_back(nextState);
            pathMoves.push_back(move);

            double t = idastarSearch(path, pathMoves, g + 1, bound, visited);
            if (t == -1.0) return -1.0;
            if (t < minBound) minBound = t;

            path.pop_back();
            pathMoves.pop_back();
            visited.erase(nextState);
        }
    }
    return minBound;
}

std::vector<char> solveIDAStar(const std::string& startState) {
    double bound = getHeuristic(startState);
    std::vector<std::string> path = {startState};
    std::vector<char> pathMoves;
    std::unordered_set<std::string> visited = {startState};

    while (true) {
        double t = idastarSearch(path, pathMoves, 0, bound, visited);
        if (t == -1.0) return pathMoves;
        if (t == std::numeric_limits<double>::infinity()) return {};
        bound = t;
    }
}