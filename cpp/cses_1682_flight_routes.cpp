#include <bits/stdc++.h>
using namespace std;

vector<int> adj[100005];
vector<int> adj2[100005];

int total_visited;
bool visited[100005];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;

    total_visited++;

    for (int adjacent: adj[node])
        dfs(adjacent);
}

void dfs2(int node) {
    if (visited[node]) return;
    visited[node] = true;

    total_visited++;

    for (int adjacent: adj2[node])
        dfs2(adjacent);
}

int main() {
    int n, m; cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj2[b].push_back(a);
    }

    dfs(1);

    if (total_visited != n) {
        for (int i = 1; i < n+1; i++) {
            if (!visited[i]) {
                cout << "NO" << endl;
                cout << "1 " << i << endl;
                return 0;
            }
        }
    }

    total_visited = 0;
    fill(visited, end(visited), false);
    dfs2(1);

    if (total_visited != n) {
        for (int i = 1; i < n+1; i++) {
            if (!visited[i]) {
                cout << "NO" << endl;
                cout << i << " 1" << endl;
                return 0;
            }
        }
    }

    cout << "YES" << endl;
}