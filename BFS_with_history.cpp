#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> solutions; // global to store all successful paths

void bfs_with_history(unordered_map<char, vector<char>> &graph, char start, char goal) {
    queue<pair<char, vector<char>>> q;
    q.push({start, {start}});

    while (!q.empty()) {
        auto [node, path] = q.front();
        q.pop();

        if (node == goal) {
            solutions.push_back(path);
            continue; // do not expand further from goal
        }

        // Use local visited tracking for each path to avoid cycles in that path
        unordered_set<char> localVisited(path.begin(), path.end());

        for (char neigh : graph[node]) {
            if (!localVisited.count(neigh)) {
                vector<char> newPath = path;
                newPath.push_back(neigh);
                q.push({neigh, newPath});
            }
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

    bfs_with_history(graph, 'S', 'G');

    cout << "All paths found:\n";
    for (auto &p : solutions) {
        for (char c : p) cout << c << " ";
        cout << "\n";
    }
}
