#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> foundRoutes;

bool climbHill(unordered_map<char, vector<pair<char, int>>> &graphMap,
               unordered_map<char, int> &heuristicMap,
               char currentNode, char targetNode,
               vector<char> &route, unordered_set<char> &visitedSet) {
    
    if (currentNode == targetNode) {
        foundRoutes.push_back(route);
        return true;
    }

    vector<pair<char, int>> candidates = graphMap[currentNode];
    sort(candidates.begin(), candidates.end(), [&](auto &a, auto &b) {
        return heuristicMap[a.first] < heuristicMap[b.first];
    });

    for (auto &[neighbor, cost] : candidates) {
        if (!visitedSet.count(neighbor)) {
            visitedSet.insert(neighbor);
            route.push_back(neighbor);

            if (climbHill(graphMap, heuristicMap, neighbor, targetNode, route, visitedSet))
                return true;

            route.pop_back();
            visitedSet.erase(neighbor);
        }
    }
    return false;
}

int main() {
    unordered_map<char, vector<pair<char, int>>> graphMap;
    graphMap['S'] = {{'A', 3}, {'B', 5}};
    graphMap['A'] = {{'D', 3}, {'B', 4}, {'S', 3}};
    graphMap['B'] = {{'A', 4}, {'C', 4}, {'S', 5}};
    graphMap['C'] = {{'E', 6}, {'B', 6}};
    graphMap['D'] = {{'A', 3}, {'G', 5}};
    graphMap['E'] = {{'C', 6}};
    graphMap['G'] = {{'D', 5}};

    unordered_map<char, int> heuristicMap = {
        {'S', 10}, {'A', 7}, {'B', 6}, {'C', 7}, {'D', 5}, {'E', 6}, {'G', 0}
    };

    vector<char> currentRoute;
    unordered_set<char> visitedSet;

    char startNode = 'S';
    char goalNode = 'G';

    visitedSet.insert(startNode);
    currentRoute.push_back(startNode);

    climbHill(graphMap, heuristicMap, startNode, goalNode, currentRoute, visitedSet);

    for (auto &path : foundRoutes) {
        for (char step : path) cout << step << " ";
        cout << "\n";
    }
}
