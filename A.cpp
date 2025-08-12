#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <algorithm>
using namespace std;

int deepRouteSearch(unordered_map<char, vector<pair<char, int>>>& cityMap,
                    char startCity, char endCity,
                    vector<char>& route, int travelledCost) 
{
    if (startCity == endCity) {
        cout << "Route: ";
        for (char step : route) cout << step << " ";
        cout << "| Total: " << travelledCost << "\n";
        return travelledCost;
    }

    int bestSoFar = INT_MAX;
    for (auto& link : cityMap[startCity]) {
        if (find(route.begin(), route.end(), link.first) == route.end()) {
            route.push_back(link.first);
            bestSoFar = min(bestSoFar, deepRouteSearch(cityMap, link.first, endCity, route, travelledCost + link.second));
            route.pop_back();
        }
    }
    return bestSoFar;
}

using JourneyState = pair<int, pair<int, pair<char, vector<char>>>>;

int guidedAStar(unordered_map<char, vector<pair<char, int>>>& cityMap,
                unordered_map<char, int>& guessMap,
                char origin, char target, int maxAllowed) 
{
    priority_queue<JourneyState, vector<JourneyState>, greater<JourneyState>> frontier;
    vector<char> startRoute = {origin};
    frontier.push({guessMap[origin], {0, {origin, startRoute}}});

    unordered_set<char> checked;
    int bestFound = INT_MAX;

    while (!frontier.empty()) {
        auto [estTotal, innerData] = frontier.top();
        auto [realCost, travelData] = innerData;
        auto [currentCity, route] = travelData;
        frontier.pop();

        int modifiedCost = realCost + (route.size() % 2);

        if (modifiedCost > maxAllowed || realCost > bestFound) continue;

        if (currentCity == target) {
            if (realCost < bestFound) bestFound = realCost;
            cout << "Route: ";
            for (char step : route) cout << step << " ";
            cout << "| Total: " << realCost << "\n";
            continue;
        }

        if (checked.count(currentCity)) continue;
        checked.insert(currentCity);

        for (auto& link : cityMap[currentCity]) {
            if (!checked.count(link.first)) {
                int gVal = realCost + link.second;
                int fVal = gVal + guessMap[link.first];
                if (gVal < bestFound) {
                    vector<char> newRoute = route;
                    newRoute.push_back(link.first);
                    frontier.push({fVal, {gVal, {link.first, newRoute}}});
                }
            }
        }
    }
    return (bestFound == INT_MAX) ? -1 : bestFound;
}

int main() {
    unordered_map<char, vector<pair<char, int>>> cityMap = {
        {'S', {{'A', 3}, {'B', 5}}},
        {'A', {{'D', 3}, {'B', 4}}},
        {'B', {{'A', 4}, {'C', 4}}},
        {'C', {{'E', 6}}},
        {'D', {{'A', 3}, {'G', 5}}},
        {'E', {{'C', 6}}},
        {'G', {{'D', 5}}}
    };

    unordered_map<char, int> estimate = {
        {'S', 10}, {'A', 7}, {'B', 6}, {'C', 7}, {'D', 5}, {'E', 6}, {'G', 0}
    };

    char source = 'S';
    char destination = 'G';

    cout << "\n>> Deep Route Exploration <<\n";
    vector<char> initRoute = {source};
    int minOracle = deepRouteSearch(cityMap, source, destination, initRoute, 0);

    if (minOracle == INT_MAX) {
        cout << "No connection found.\n";
        return 0;
    } else {
        cout << "Shortest possible path length: " << minOracle << "\n";
    }

    cout << "\n>> Guided A* Execution <<\n";
    int finalResult = guidedAStar(cityMap, estimate, source, destination, minOracle);

    if (finalResult == -1)
        cout << "No path found within constraints.\n";
    else
        cout << "Best cost discovered: " << finalResult << "\n";

    return 0;
}
