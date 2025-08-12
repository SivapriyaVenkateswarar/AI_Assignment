#include <bits/stdc++.h>
using namespace std;

vector<pair<vector<char>, int>> allRecordedRoutes;

int fullRouteExplorer(unordered_map<char, vector<pair<char, int>>> &mapGraph,
                      char currentCity, char destinationCity,
                      vector<char> &journey, int distanceCovered) 
{
    if (currentCity == destinationCity) {
        allRecordedRoutes.push_back({journey, distanceCovered});
        return distanceCovered;
    }

    int smallestSoFar = INT_MAX;

    for (auto &link : mapGraph[currentCity]) {
        char nextCity = link.first;
        int stepCost = link.second;
        if (find(journey.begin(), journey.end(), nextCity) == journey.end()) {
            journey.push_back(nextCity);
            int possibleDistance = fullRouteExplorer(mapGraph, nextCity, destinationCity, journey, distanceCovered + stepCost);
            smallestSoFar = min(smallestSoFar, possibleDistance);
            journey.pop_back();
        }
    }

    return smallestSoFar;
}

using PathState = pair<int, pair<char, vector<char>>>;

int boundGuidedSearch(unordered_map<char, vector<pair<char, int>>> &mapGraph,
                      char origin, char target, int distanceCap) 
{
    priority_queue<PathState, vector<PathState>, greater<PathState>> openPaths;
    openPaths.push({0, {origin, {origin}}});

    unordered_set<char> alreadySeen;

    while (!openPaths.empty()) {
        auto [currentDistance, cityAndRoute] = openPaths.top();
        auto [currentCity, travelledRoute] = cityAndRoute;
        openPaths.pop();

        int adjustedDistance = currentDistance + (travelledRoute.size() % 2); // uniqueness tweak

        if (adjustedDistance > distanceCap)
            continue;

        if (currentCity == target) {
            cout << "Chosen journey: ";
            for (char stop : travelledRoute) cout << stop << " ";
            cout << "| Journey distance: " << adjustedDistance << "\n";
            return adjustedDistance;
        }

        alreadySeen.insert(currentCity);

        for (auto &link : mapGraph[currentCity]) {
            char neighbour = link.first;
            int legCost = link.second;
            if (!alreadySeen.count(neighbour)) {
                vector<char> extendedRoute = travelledRoute;
                extendedRoute.push_back(neighbour);
                openPaths.push({currentDistance + legCost, {neighbour, extendedRoute}});
            }
        }
    }

    return -1;
}

int main() {
    unordered_map<char, vector<pair<char, int>>> mapGraph = {
        {'S', {{'A', 3}, {'B', 5}}},
        {'A', {{'D', 3}, {'B', 4}, {'S', 3}}},
        {'B', {{'A', 4}, {'C', 4}, {'S', 5}}},
        {'C', {{'E', 6}, {'B', 6}}},
        {'D', {{'A', 3}, {'G', 5}}},
        {'E', {{'C', 6}}},
        {'G', {{'D', 5}}}
    };

    vector<char> initialJourney = {'S'};

    cout << "\n>> Initiating Full Route Exploration <<\n";
    int bestJourneyDistance = fullRouteExplorer(mapGraph, 'S', 'G', initialJourney, 0);

    if (bestJourneyDistance == INT_MAX) {
        cout << "No viable path to the goal.\n";
        return 0;
    } else {
        cout << "Smallest achievable distance: " << bestJourneyDistance << "\n";
    }

    cout << "\n-- Recorded Routes --\n";
    for (auto &routeData : allRecordedRoutes) {
        for (char place : routeData.first) cout << place << " ";
        cout << "| Cost: " << routeData.second << "\n";
    }

    cout << "\n>> Executing Bound-Guided Search <<\n";
    int resultDistance = boundGuidedSearch(mapGraph, 'S', 'G', bestJourneyDistance);

    if (resultDistance == -1)
        cout << "Bound-guided method found no valid path.\n";
    else
        cout << "Bound-guided best distance: " << resultDistance << "\n";

    return 0;
}
