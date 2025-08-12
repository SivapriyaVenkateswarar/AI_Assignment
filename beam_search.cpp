#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> finalPaths;

bool runBeamSearch(unordered_map<char, vector<pair<char, int>>> &graphMap,
                   unordered_map<char, int> &heuristicMap,
                   char startNode, char targetNode, size_t beamLimit) {
    
    auto compare = [&](const pair<char, vector<char>> &a, const pair<char, vector<char>> &b) {
        return heuristicMap[a.first] > heuristicMap[b.first];
    };

    priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(compare)> activeBeam(compare);
    activeBeam.push({startNode, {startNode}});

    while (!activeBeam.empty()) {
        priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(compare)> nextBeam(compare);

        while (!activeBeam.empty()) {
            auto [currentNode, currentPath] = activeBeam.top();
            activeBeam.pop();

            if (currentNode == targetNode) {
                finalPaths.push_back(currentPath);
                return true;
            }

            for (auto &[neighbor, cost] : graphMap[currentNode]) {
                vector<char> updatedPath = currentPath;
                updatedPath.push_back(neighbor);
                nextBeam.push({neighbor, updatedPath});
            }
        }

        vector<pair<char, vector<char>>> selected;
        while (!nextBeam.empty() && selected.size() < beamLimit) {
            selected.push_back(nextBeam.top());
            nextBeam.pop();
        }

        for (auto &item : selected) activeBeam.push(item);
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

    size_t beamWidth = 2;

    runBeamSearch(graphMap, heuristicMap, 'S', 'G', beamWidth);

    for (auto &path : finalPaths) {
        for (char step : path) cout << step << " ";
        cout << "\n";
    }
}
