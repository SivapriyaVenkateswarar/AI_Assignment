#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> allSolutions;
unordered_set<char> seenNodes;

bool beamSearchWithHistory(unordered_map<char, vector<pair<char, int>>> &network,
                           unordered_map<char, int> &priorityMap,
                           char source, char target,
                           size_t widthLimit) 
{
    auto comparePriority = [&](const pair<char, vector<char>> &a, const pair<char, vector<char>> &b) {
        return priorityMap[a.first] > priorityMap[b.first];
    };

    priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(comparePriority)> activeLevel(comparePriority);
    activeLevel.push({source, {source}});
    seenNodes.insert(source);

    while (!activeLevel.empty()) {
        priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(comparePriority)> nextLevel(comparePriority);

        while (!activeLevel.empty()) {
            auto current = activeLevel.top();
            activeLevel.pop();

            char node = current.first;
            vector<char> route = current.second;

            if (node == target) {
                allSolutions.push_back(route);
                return true;
            }

            for (auto &link : network[node]) {
                char neighbor = link.first;
                if (!seenNodes.count(neighbor)) {
                    vector<char> extendedPath = route;
                    extendedPath.push_back(neighbor);
                    nextLevel.push({neighbor, extendedPath});
                }
            }
        }

        vector<pair<char, vector<char>>> chosen;
        while (!nextLevel.empty() && chosen.size() < widthLimit) {
            chosen.push_back(nextLevel.top());
            seenNodes.insert(nextLevel.top().first);
            nextLevel.pop();
        }

        for (auto &entry : chosen) {
            activeLevel.push(entry);
        }
    }

    return false;
}

int main() {
    unordered_map<char, vector<pair<char, int>>> network;
    network['S'] = {{'A', 3}, {'B', 5}};
    network['A'] = {{'D', 3}, {'B', 4}, {'S', 3}};
    network['B'] = {{'A', 4}, {'C', 4}, {'S', 5}};
    network['C'] = {{'E', 6}, {'B', 6}};
    network['D'] = {{'A', 3}, {'G', 5}};
    network['E'] = {{'C', 6}};
    network['G'] = {{'D', 5}};

    unordered_map<char, int> priorityMap = {
        {'S', 10}, {'A', 7}, {'B', 6}, {'C', 7}, {'D', 5}, {'E', 6}, {'G', 0}
    };

    size_t beamLimit = 2;

    if (!beamSearchWithHistory(network, priorityMap, 'S', 'G', beamLimit)) {
        cout << "No route found\n";
    }

    for (auto &solution : allSolutions) {
        for (char step : solution) cout << step << " ";
        cout << "\n";
    }

    return 0;
}
