#include <bits/stdc++.h>
using namespace std;

vector<int> adj[100005];
bool visited[100005];

using ll = long long;

ll true_nodes = 0;
ll false_nodes = 0;

void dfs(int node, bool val) {
    if (visited[node]) {
        return;
    }

    visited[node] = true;

    if (val) {
        true_nodes++;
    } else {
        false_nodes++;
    }

    for (int adj_node: adj[node])
        dfs(adj_node, !val);
}

int main() {
    int n; cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, false);

    ll ans = (true_nodes * false_nodes) - (n - 1);

    cout << ans;
}