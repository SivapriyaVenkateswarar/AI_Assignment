#include <bits/stdc++.h>
using namespace std;

vector<string> res;
bool done = false;

void goDFS(map<string, vector<string>> &g, string u, string t, vector<string> &p, set<string> &vis) {
    if (u == t) {
        res = p;
        done = true;
        return;
    }
    for (auto &v : g[u]) {
        if (!vis.count(v)) {
            vis.insert(v);
            p.push_back(v);
            goDFS(g, v, t, p, vis);
            if (done) return;
            p.pop_back();
            vis.erase(v);
        }
    }
}

void hybrid(map<string, vector<string>> &g, string s, string t, int swDepth) {
    queue<pair<string, vector<string>>> q;
    q.push({s, {s}});
    while (!q.empty() && !done) {
        auto [u, p] = q.front(); q.pop();
        if ((int)p.size() - 1 >= swDepth) {
            set<string> vis(p.begin(), p.end());
            goDFS(g, u, t, p, vis);
            return;
        }
        for (auto &v : g[u]) {
            if (find(p.begin(), p.end(), v) == p.end()) {
                auto np = p;
                np.push_back(v);
                q.push({v, np});
            }
        }
    }
}

int main() {
    map<string, vector<string>> g;
    g["S"] = {"A", "B"};
    g["A"] = {"D", "B", "S"};
    g["B"] = {"A", "C", "S"};
    g["C"] = {"E", "B"};
    g["D"] = {"A", "G"};
    g["E"] = {"C"};
    g["G"] = {"D"};

    hybrid(g, "S", "G", 2);

    cout << "Path from S to G: ";
    for (int i = 0; i < res.size(); i++) {
        cout << res[i];
        if (i + 1 < res.size()) cout << " -> ";
    }
    cout << "\n";
}
