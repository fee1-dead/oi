#include <bits/stdc++.h>
using namespace std;
int visited[100000] = {true};
int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj = vector<vector<int>>(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    queue<int> q;
    vector<int> parent(n);
    q.push(0);
    while(!q.empty()) {
        int entry = q.front(); q.pop();
        for(int adjacent: adj[entry]) {
            if(visited[adjacent]) continue;
            visited[adjacent] = true;
            q.push(adjacent);
            parent[adjacent] = entry;
        }
    }
    if(visited[n-1]) {
        vector<int> v = {n-1}; while(v.back() != 0) v.push_back(parent[v.back()]);
        reverse(v.begin(), v.end());
        cout << v.size() << "\n";
        for(int i = 0; i < v.size(); i++) {
            if (i != 0) cout << ' ';
            cout << v[i]+1;
        }
        cout << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }   
}