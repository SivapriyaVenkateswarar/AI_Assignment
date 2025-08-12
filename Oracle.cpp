#include <bits/stdc++.h>
using namespace std;

int exploreAllPaths(unordered_map<char, vector<pair<char, int>>>& roadMap,
                    char currentCity, char targetCity,
                    vector<char>& currentRoute, int totalDistance) 
{
    if (currentCity == targetCity) {
        cout << "Route: ";
        for (char stop : currentRoute) cout << stop << " ";
        cout << "| Total Distance: " << totalDistance << "\n";
        return totalDistance;
    }

    int shortestDistance = INT_MAX;

    for (auto& connection : roadMap[currentCity]) {
        char nextCity = connection.first;
        int travelCost = connection.second;

        if (find(currentRoute.begin(), currentRoute.end(), nextCity) == currentRoute.end()) {
            currentRoute.push_back(nextCity);
            int candidateDistance = exploreAllPaths(roadMap, nextCity, targetCity, currentRoute, totalDistance + travelCost);
            shortestDistance = min(shortestDistance, candidateDistance);
            currentRoute.pop_back();
        }
    }

    return shortestDistance;
}

int main() {
    unordered_map<char, vector<pair<char, int>>> roadMap = {
        {'S', {{'A', 3}, {'B', 5}}},
        {'A', {{'D', 3}, {'B', 4}, {'S', 3}}},
        {'B', {{'A', 4}, {'C', 4}, {'S', 5}}},
        {'C', {{'E', 6}, {'B', 6}}},
        {'D', {{'A', 3}, {'G', 5}}},
        {'E', {{'C', 6}}},
        {'G', {{'D', 5}}}
    };

    vector<char> travelHistory = {'S'};
    int bestDistance = exploreAllPaths(roadMap, 'S', 'G', travelHistory, 0);

    if (bestDistance == INT_MAX) {
        cout << "No possible route to reach the destination.\n";
    } else {
        cout << "Oracle shortest distance: " << bestDistance << "\n";
    }

    return 0;
}
