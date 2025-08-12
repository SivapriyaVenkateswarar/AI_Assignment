#include <bits/stdc++.h>
using namespace std;

bool hillClimbSearch(unordered_map<char, vector<pair<char, int>>> &graphMap,
                     unordered_map<char, int> &heuristicMap,
                     char current, char goal,
                     unordered_set<char> &visitedNodes,
                     vector<char> &currentPath) 
{
    currentPath.push_back(current);

    if (current == goal) return true;

    visitedNodes.insert(current);

    vector<pair<char, int>> options = graphMap[current];
    sort(options.begin(), options.end(),
         [&](auto &left, auto &right) {
             return heuristicMap[left.first] < heuristicMap[right.first];
         });

    for (auto &[nextNode, cost] : options) {
        if (!visitedNodes.count(nextNode)) {
            if (hillClimbSearch(graphMap, heuristicMap, nextNode, goal, visitedNodes, currentPath))
                return true;
        }
    }

    currentPath.pop_back();
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

    unordered_set<char> visitedNodes;
    vector<char> pathTaken;

    if (hillClimbSearch(graphMap, heuristicMap, 'S', 'G', visitedNodes, pathTaken)) {
        for (char step : pathTaken) cout << step << " ";
        cout << "\n";
    } else {
        cout << "No path found\n";
    }
}
