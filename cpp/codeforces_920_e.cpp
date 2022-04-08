#include <bits/stdc++.h>
using namespace std;

unordered_set<int> non_adjs[200000];
set<int> not_visited;

void dfs(int node, int& v) {
    v++;
    auto iter = not_visited.begin();
    while (iter != not_visited.end()) {
        if(non_adjs[node].count(*iter)) {
            iter++;
        } else {
            int adj = *iter;
            not_visited.erase(adj);
            dfs(adj, v);
            iter = not_visited.upper_bound(adj);
        }
    }
}

int main() {
    int n, m; cin >> n >> m;

    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y; x--; y--;
        non_adjs[x].insert(y);
        non_adjs[y].insert(x);
    }

    for(int i = 0; i < n; i++) {
        not_visited.insert(i);
    }

    vector<int> comp;
    for(int i = 0; i < n; i++) {
        if(not_visited.find(i) != not_visited.end()) {
            not_visited.erase(i);
            int cnt = 0;
            dfs(i, cnt);
            comp.push_back(cnt);
        }
    }
    sort(comp.begin(), comp.end());

    cout << comp.size() << "\n";

    for(int i = 0; i < comp.size(); i++) {
        if(i) cout << " ";
        cout << comp[i];
    }
    cout << "\n";
}