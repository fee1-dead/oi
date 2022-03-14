#include <bits/stdc++.h>
using namespace std;

vector<int> adj[3005];

int total_visited;
bool visited[3005];
bool closed[3005];

void dfs(int node) {
    if (visited[node] || closed[node]) {
        return;
    }

    total_visited++;
    visited[node] = true;

    for (int adjacent_node: adj[node]) {
        dfs(adjacent_node);
    }
}

int main() {
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
    int n, m; cin >> n >> m;
    int open_barns = n;

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int starting_with = 1;

    for (int i = 0; i < n; i++) {
        total_visited = 0;
        fill(begin(visited), end(visited), false);

        dfs(starting_with);

        if (total_visited == open_barns) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

        int closing; cin >> closing;
        open_barns--;
        closed[closing] = true;
        while (closed[starting_with]) {
            starting_with++;
        }
    }
}