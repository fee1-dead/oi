#include <bits/stdc++.h>
using namespace std;

vector<int> adj[100005];
bool visited[100005];

void dfs(int node) {
    visited[node] = true;
    for (int adjacent: adj[node]) {
        if (!visited[adjacent]) {
            dfs(adjacent);
        }
    }
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1);
    vector<int> ans;
    for (int i = 2; i <= n; i++) {
        if (!visited[i]) {
            ans.push_back(i);
            dfs(i);
        }
    }
    cout << ans.size() << endl;
    for (int node: ans) {
        cout << 1 << ' ' << node << endl;
    }
}