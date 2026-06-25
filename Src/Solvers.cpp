#include "Solvers.hpp"
#include "Cube.hpp"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <algorithm>

std::vector<char> solveBFS(const std::string& startState) {
    if (startState == SOLVED_STATE) return {};

    std::queue<std::string> q;
    std::unordered_map<std::string, std::pair<std::string, char>> parentMap;

    q.push(startState);
    parentMap[startState] = {"", '\0'};

    size_t nodesExplored = 0;
    while (!q.empty() && nodesExplored < 150000) {
        std::string current = q.front();
        q.pop();
        nodesExplored++;

        for (const auto& [nextState, move] : getNeighbors(current)) {
            if (parentMap.find(nextState) == parentMap.end()) {
                parentMap[nextState] = {current, move};
                
                if (nextState == SOLVED_STATE) {
                    std::vector<char> path;
                    std::string curr = nextState;
                    while (curr != startState) {
                        auto p = parentMap[curr];
                        path.push_back(p.second);
                        curr = p.first;
                    }
                    std::reverse(path.begin(), path.end());
                    return path;
                }
                q.push(nextState);
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
    int gScore;
    std::string state;

    bool operator>(const AStarNode& other) const {
        return fScore > other.fScore;
    }
};

std::vector<char> solveAStar(const std::string& startState) {
    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;
    std::unordered_map<std::string, std::pair<std::string, char>> parentMap;
    std::unordered_map<std::string, int> gScore;

    openSet.push({getHeuristic(startState), 0, startState});
    gScore[startState] = 0;
    parentMap[startState] = {"", '\0'};

    size_t iterations = 0;
    while (!openSet.empty() && iterations < 100000) {
        auto [f, currentG, current] = openSet.top();
        openSet.pop();
        iterations++;

        if (current == SOLVED_STATE) {
            std::vector<char> path;
            std::string curr = current;
            while (curr != startState) {
                auto p = parentMap[curr];
                path.push_back(p.second);
                curr = p.first;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& [nextState, move] : getNeighbors(current)) {
            int tentativeG = currentG + 1;

            if (gScore.find(nextState) == gScore.end() || tentativeG < gScore[nextState]) {
                gScore[nextState] = tentativeG;
                parentMap[nextState] = {current, move};
                double nextF = tentativeG + getHeuristic(nextState);
                openSet.push({nextF, tentativeG, nextState});
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

    for (int depthLimit = 0; depthLimit < 10; ++depthLimit) {
        double t = idastarSearch(path, pathMoves, 0, bound, visited);
        if (t == -1.0) return pathMoves;
        if (t == std::numeric_limits<double>::infinity()) return {};
        bound = t;
    }
    return {};
}