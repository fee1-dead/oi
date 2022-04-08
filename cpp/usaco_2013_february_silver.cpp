#include <bits/stdc++.h>
using namespace std;
int grid[250000];

struct Dsu {
    vector<int> e;
    Dsu(int N) { e = vector<int>(N, -1); }
    int get(int node) {
        if (e[node] < 0) {
            return node;
        } else {
            int parent = get(e[node]);
            e[node] = parent;
            return parent;
        }
    }
    void unite(int a, int b) {
        a = get(a); b = get(b);
        if(a == b) return;
        if(e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
    }
};
int main() {
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);
    int n; cin >> n;
    int total = n * n;
    Dsu dsu = Dsu(total);
    vector<pair<int, pair<int, int>>> edges;
    for(int i = 0; i < total; i++) {
        int value; cin >> value;
        grid[i] = value;
        if (i%n > 0) {
            int adj = i-1;
            edges.push_back({abs(grid[adj] - grid[i]), {i, adj}});
        }
        if(i>=n) {
            int adj = i - n;
            edges.push_back({abs(grid[adj] - grid[i]), {i, adj}});
        }
    }
    sort(edges.begin(), edges.end());
    int numtovisit;
    if (total%2 == 1) numtovisit = total / 2 + 1;
    else numtovisit = total / 2;
    for(auto edge: edges) {
        dsu.unite(edge.second.first, edge.second.second);
        int repr = dsu.get(edge.second.first);
        int visited = -dsu.e[repr];
        if (visited >= numtovisit) {
            cout << edge.first << "\n";
            return 0;
        }
    }
}