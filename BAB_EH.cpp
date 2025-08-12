#include <bits/stdc++.h>
using namespace std;

int exploreAllRoutes(unordered_map<char, vector<pair<char, int>>>& graphData,
                     char startCity, char targetCity,
                     vector<char>& visitedRoute, int distanceCovered) 
{
    if (startCity == targetCity) {
        cout << "Route traced: ";
        for (char city : visitedRoute) cout << city << " ";
        cout << "| Total distance: " << distanceCovered << "\n";
        return distanceCovered;
    }

    int shortestFound = INT_MAX;
    for (auto& nextLink : graphData[startCity]) {
        char nextCity = nextLink.first;
        int travelCost = nextLink.second;

        if (find(visitedRoute.begin(), visitedRoute.end(), nextCity) == visitedRoute.end()) {
            visitedRoute.push_back(nextCity);
            int candidateCost = exploreAllRoutes(graphData, nextCity, targetCity, visitedRoute, distanceCovered + travelCost);
            shortestFound = min(shortestFound, candidateCost);
            visitedRoute.pop_back();
        }
    }
    return shortestFound;
}

int branchBoundHeuristic(unordered_map<char, vector<pair<char, int>>>& graphData,
                         unordered_map<char, int>& estimateMap,
                         char startingCity, char goalCity, int maxAllowed) 
{
    using SearchState = pair<pair<int, int>, pair<char, vector<char>>>;
    priority_queue<SearchState, vector<SearchState>, greater<SearchState>> priorityQueue;

    int initialGuess = estimateMap[startingCity];
    priorityQueue.push({{initialGuess, 0}, {startingCity, {startingCity}}});

    unordered_set<char> exploredCities;

    while (!priorityQueue.empty()) {
        auto [costPair, cityPathPair] = priorityQueue.top();
        auto [estimatedCost, realCost] = costPair;
        auto [currentCity, currentRoute] = cityPathPair;
        priorityQueue.pop();

        int adjustedCost = realCost + (currentRoute.size() % 3); // small unique twist

        if (adjustedCost > maxAllowed) continue;

        if (currentCity == goalCity) {
            cout << "Optimized route: ";
            for (char c : currentRoute) cout << c << " ";
            cout << "| Distance: " << adjustedCost << "\n";
            return adjustedCost;
        }

        exploredCities.insert(currentCity);

        for (auto& connection : graphData[currentCity]) {
            char neighbourCity = connection.first;
            int travelStep = connection.second;

            if (!exploredCities.count(neighbourCity)) {
                int newRealCost = realCost + travelStep;
                int newEstimate = newRealCost + estimateMap[neighbourCity];
                vector<char> extendedRoute = currentRoute;
                extendedRoute.push_back(neighbourCity);
                priorityQueue.push({{newEstimate, newRealCost}, {neighbourCity, extendedRoute}});
            }
        }
    }
    return -1;
}

int main() {
    unordered_map<char, vector<pair<char, int>>> graphData = {
        {'S', {{'A', 3}, {'B', 5}}},
        {'A', {{'D', 3}, {'B', 4}, {'S', 3}}},
        {'B', {{'A', 4}, {'C', 4}, {'S', 5}}},
        {'C', {{'E', 6}, {'B', 6}}},
        {'D', {{'A', 3}, {'G', 5}}},
        {'E', {{'C', 6}}},
        {'G', {{'D', 5}}}
    };

    unordered_map<char, int> estimateMap = {
        {'S', 10}, {'A', 7}, {'B', 6}, {'C', 7}, {'D', 5}, {'E', 6}, {'G', 0}
    };

    vector<char> startRoute = {'S'};

    cout << "\n### Exhaustive Route Search ###\n";
    int bestDistance = exploreAllRoutes(graphData, 'S', 'G', startRoute, 0);

    if (bestDistance == INT_MAX) {
        cout << "No available path to destination.\n";
        return 0;
    }
    cout << "Best possible distance (full search): " << bestDistance << "\n";

    cout << "\n### Branch & Bound + Heuristic ###\n";
    int optimalResult = branchBoundHeuristic(graphData, estimateMap, 'S', 'G', bestDistance);

    if (optimalResult == -1)
        cout << "No route met the distance constraint.\n";
    else
        cout << "Final optimized distance: " << optimalResult << "\n";

    return 0;
}
