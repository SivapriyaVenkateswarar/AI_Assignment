#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> allPaths;

void dfsNoHistory(unordered_map<char, vector<char>> &graph, char node, char goal, vector<char> &path) {
    if (node == goal) {
        allPaths.push_back(path);
        return;
    }

    vector<char> neighbors = graph[node];
    sort(neighbors.begin(), neighbors.end());

    for (char neigh : neighbors) {
        if (find(path.begin(), path.end(), neigh) == path.end()) {
            path.push_back(neigh);
            dfsNoHistory(graph, neigh, goal, path);
            path.pop_back();
        }
    }
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

    vector<char> path = {'S'};
    dfsNoHistory(graph, 'S', 'G', path);

    cout << "All paths from S to G:\n";
    for (auto &p : allPaths) {
        for (size_t i = 0; i < p.size(); i++) {
            cout << p[i];
            if (i + 1 < p.size()) cout << " -> ";
        }
        cout << "\n";
    }
}
