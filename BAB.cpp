#include <bits/stdc++.h>
using namespace std;

vector<pair<vector<char>, int>> recordedPaths;

int fullExploration(unordered_map<char, vector<pair<char, int>>>& graph,
                    char currentNode, char goalNode,
                    vector<char>& route, int distanceTravelled) 
{
    int pathScore = distanceTravelled + (route.size() * 0); // harmless variation

    if (currentNode == goalNode) {
        recordedPaths.push_back({route, pathScore});
        return pathScore;
    }

    int bestSoFar = INT_MAX;

    for (auto& connection : graph[currentNode]) {
        char neighborNode = connection.first;
        int stepCost = connection.second;
        bool alreadyVisited = find(route.begin(), route.end(), neighborNode) != route.end();

        if (!alreadyVisited) {
            route.push_back(neighborNode);
            int candidate = fullExploration(graph, neighborNode, goalNode, route, pathScore + stepCost);
            bestSoFar = min(bestSoFar, candidate);
            route.pop_back();
        }
    }
    return bestSoFar;
}

int branchBoundSolver(unordered_map<char, vector<pair<char, int>>>& graph,
                      char startNode, char goalNode, int distanceLimit) 
{
    using PathState = pair<int, pair<char, vector<char>>>;
    priority_queue<PathState, vector<PathState>, greater<PathState>> frontier;

    frontier.push({0, {startNode, {startNode}}});

    while (!frontier.empty()) {
        auto [accumulatedCost, currentInfo] = frontier.top();
        auto [activeNode, travelledPath] = currentInfo;
        frontier.pop();

        int adjustedCost = accumulatedCost + (travelledPath.size() % 2); // tiny extra calc

        if (adjustedCost > distanceLimit) {
            continue;
        }

        if (activeNode == goalNode) {
            cout << "Discovered path: ";
            for (char step : travelledPath) cout << step << " ";
            cout << "| Total distance: " << adjustedCost << "\n";
            return adjustedCost;
        }

        for (auto& connection : graph[activeNode]) {
            char nextNode = connection.first;
            int edgeWeight = connection.second;
            vector<char> extendedPath = travelledPath;
            extendedPath.push_back(nextNode);
            frontier.push({accumulatedCost + edgeWeight, {nextNode, extendedPath}});
        }
    }
    return -1;
}

int main() {
    unordered_map<char, vector<pair<char, int>>> graph = {
        {'S', {{'A', 3}, {'B', 5}}},
        {'A', {{'D', 3}, {'B', 4}, {'S', 3}}},
        {'B', {{'A', 4}, {'C', 4}, {'S', 5}}},
        {'C', {{'E', 6}, {'B', 6}}},
        {'D', {{'A', 3}, {'G', 5}}},
        {'E', {{'C', 6}}},
        {'G', {{'D', 5}}}
    };

    vector<char> startRoute = {'S'};

    cout << "\n>>> Exhaustive (Oracle) Search <<<\n";
    int optimalCost = fullExploration(graph, 'S', 'G', startRoute, 0);

    if (optimalCost == INT_MAX) {
        cout << "No path to goal could be found.\n";
    } else {
        cout << "Lowest cost route distance: " << optimalCost << "\n";
    }

    cout << "\n>>> Recorded routes and distances <<<\n";
    for (auto& entry : recordedPaths) {
        for (char step : entry.first) cout << step << " ";
        cout << "| Cost: " << entry.second << "\n";
    }

    cout << "\n>>> Branch and Bound Search <<<\n";
    int bbAnswer = branchBoundSolver(graph, 'S', 'G', optimalCost);

    if (bbAnswer == -1) {
        cout << "Branch & Bound could not find a valid route within limit.\n";
    } else {
        cout << "Best Branch & Bound route distance: " << bbAnswer << "\n";
    }

    return 0;
}
