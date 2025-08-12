#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> solutions;

struct cmp {
    bool operator()(const pair<char, vector<char>> &a, const pair<char, vector<char>> &b) const {
        if (a.second.size() != b.second.size())
            return a.second.size() > b.second.size();
        return a.second > b.second;
    }
};

bool shortestPath(const vector<vector<int>> &g, int start, int goal, vector<int> &path) {
    int n = g.size();
    queue<int> q;
    q.push(start);
    vector<bool> vis(n, false);
    vis[start] = true;
    vector<int> parent(n, -1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == goal) {
            path.clear();
            for (int p = goal; p != -1; p = parent[p]) path.push_back(p);
            reverse(path.begin(), path.end());
            return true;
        }
        for (int v = 0; v < n; v++) {
            if (g[u][v] && !vis[v]) {
                vis[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    return false;
}

void bms(unordered_map<char, vector<char>> &g, char start, char goal) {
    priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, cmp> pq;
    pq.push({start, {start}});
    while (!pq.empty()) {
        auto [node, path] = pq.top(); pq.pop();
        if (node == goal) {
            solutions.push_back(path);
            continue;
        }
        vector<char> nbrs = g[node];
        sort(nbrs.begin(), nbrs.end());
        for (char nxt : nbrs) {
            if (find(path.begin(), path.end(), nxt) == path.end()) {
                auto newPath = path;
                newPath.push_back(nxt);
                pq.push({nxt, newPath});
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

    bms(graph, 'S', 'G');

    cout << "All paths found:\n";
    for (auto &p : solutions) {
        for (char c : p) cout << c << " ";
        cout << "\n";
    }

    int n;
    cout << "\nEnter number of nodes: ";
    cin >> n;
    vector<vector<int>> mat(n, vector<int>(n));
    char ch;
    for (int i = 0; i < n; i++) {
        cin >> ch;
        for (int j = 0; j < n; j++) cin >> mat[i][j];
        cin >> ch;
    }
    vector<int> spath;
    if (shortestPath(mat, 0, n - 1, spath)) {
        cout << "Shortest path length: " << spath.size() - 1 << "\nPath: ";
        for (int p : spath) cout << p << " ";
        cout << "\n";
    } else {
        cout << "No path found\n";
    }
}
