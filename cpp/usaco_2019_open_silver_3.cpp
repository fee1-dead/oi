#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define f first;
#define s second;

pair<ll, ll> pos[100005];
vector<int> adj[100005];

bool visited[100005];

ll minX = 10000000000, minY = 10000000000, maxX = -1, maxY = -1;

void dfs(int node) {
    if (visited[node]) {
        return;
    }

    visited[node] = true;

    auto position = pos[node];

    minX = min(position.first, minX);
    maxX = max(position.first, maxX);
    minY = min(position.second, minY);
    maxY = max(position.second, maxY);

    for (int adjacent: adj[node])
        dfs(adjacent);
}

int main() {
    freopen("fenceplan.in", "r", stdin);
    freopen("fenceplan.out", "w", stdout);
    int n, m; cin >> n >> m;

    for (int i = 1; i < n+1; i++) {
        ll x, y; cin >> x >> y;
        pos[i] = make_pair(x, y);
    } 

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    ll minPrim = 10000000000;
    for (int i = 1; i < n+1; i++) {
        minX = 10000000000, minY = 10000000000, maxX = -1, maxY = -1;

        if (visited[i])
            continue;

        dfs(i);

        ll prim = 2 * (maxX - minX + maxY - minY);
        minPrim = min(prim, minPrim);
    }

    cout << minPrim << endl;
}