#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> allPaths;

void bfsNoHistory(map<string, vector<string>> &graph, string start, string goal) {
    queue<vector<string>> q;
    q.push({start});

    while (!q.empty()) {
        vector<string> path = q.front();
        q.pop();
        string node = path.back();

        if (node == goal) {
            allPaths.push_back(path);
            continue;
        }

        vector<string> neighbors = graph[node];
        sort(neighbors.begin(), neighbors.end());

        for (auto &n : neighbors) {
            if (find(path.begin(), path.end(), n) == path.end()) {
                vector<string> newPath = path;
                newPath.push_back(n);
                q.push(newPath);
            }
        }
    }
}

int main() {
    map<string, vector<string>> graph;
    graph["S"] = {"A", "B"};
    graph["A"] = {"D", "B", "S"};
    graph["B"] = {"A", "C", "S"};
    graph["C"] = {"E", "B"};
    graph["D"] = {"A", "G"};
    graph["E"] = {"C"};
    graph["G"] = {"D"};

    bfsNoHistory(graph, "S", "G");

    cout << "All paths from S to G:\n";
    for (auto &p : allPaths) {
        for (size_t i = 0; i < p.size(); i++) {
            cout << p[i];
            if (i + 1 < p.size()) cout << " -> ";
        }
        cout << "\n";
    }
}

