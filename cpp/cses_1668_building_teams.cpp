#include <bits/stdc++.h>
using namespace std;

vector<int> adj[100000];
bool value[100000], visited[100000];

void dfs(int node=0, bool val=false) {
    visited[node] = true;
    value[node] = val;
    for(auto adjacent: adj[node]) {
        if (visited[adjacent]) {
            if (value[adjacent] == val) {
                cout << "IMPOSSIBLE" << endl;
                exit(0);
            }
        } else {
            dfs(adjacent, !val);
        }
    }
}

int main() {
    int n,m;
    cin >> n >> m;
    for (int i = 0; i<m; i++) {
        int a, b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b); adj[b].push_back(a);
    }

    for(int i = 0; i<n; i++) {
        if(visited[i]) continue;
        dfs(i);
    }
    for(int i = 0; i<n; i++) {
        if(i!=0) cout << " ";
        int val = value[i];
        cout << val + 1;
    }
    cout << endl;
}