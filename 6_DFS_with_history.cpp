#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> allRoutes;

bool DFS_with_history(unordered_map<char, vector<char>> &graph, char current, char destination,
                  vector<char> &currentPath, unordered_set<char> &visitedNodes, unordered_set<char> &blockedNodes) {
    if (blockedNodes.count(current)) return false;
    if (current == destination) {
        allRoutes.push_back(currentPath);
        return true;
    }

    vector<char> nextStops = graph[current];
    sort(nextStops.begin(), nextStops.end());

    bool reached = false;
    for (char neighbor : nextStops) {
        if (!visitedNodes.count(neighbor)) {
            visitedNodes.insert(neighbor);
            currentPath.push_back(neighbor);

            if (DFS_with_history(graph, neighbor, destination, currentPath, visitedNodes, blockedNodes))
                reached = true;

            currentPath.pop_back();
            visitedNodes.erase(neighbor);
        }
    }

    if (!reached) blockedNodes.insert(current);
    return reached;
}

int main() {
    unordered_map<char, vector<char>> graph;
    graph['S'] = {'A', 'B'};
    graph['A'] = {'D', 'B', 'S'};
    graph['B'] = {'A', 'C', 'S'};
    graph['C'] = {'E', 'B'};
    graph['D'] = {'A', 'G'};
    graph['E'] = {'C'};
    graph['G'] = {'D'};

    vector<char> route;
    unordered_set<char> visited, blocked;
    char startPoint = 'S';
    char endPoint = 'G';

    visited.insert(startPoint);
    route.push_back(startPoint);

    DFS_with_history(graph, startPoint, endPoint, route, visited, blocked);

    for (auto &path : allRoutes) {
        for (char step : path) cout << step << " ";
        cout << "\n";
    }
}
