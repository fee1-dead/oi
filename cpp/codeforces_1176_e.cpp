// try to color graph as bipartite, we end up with nodes
// evenly divided, then print nodes with desired value
#include <bits/stdc++.h>
using namespace std;
void dfs(
    vector<bool>& values,
    vector<bool>& visited,
    vector<vector<int>>& adjacent,
    int& count,
    int node=0,
    bool value=false
) {
    if (visited[node]) return;
    values[node] = value;
    visited[node] = true;
    if (value) count++;
    for(auto adjacent_node: adjacent[node]) {
        dfs(values, visited, adjacent, count, adjacent_node, !value);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t; cin >> t;
    for (int cs = 0; cs < t; cs++) {
        int n, m; cin >> n >> m;
        vector<bool> values(n);
        vector<bool> visited(n);
        vector<vector<int>> adjacent(n);
        int count = 0;
        bool find = true;
        for(int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            a--; b--;
            adjacent[a].push_back(b);
            adjacent[b].push_back(a);
        }
        dfs(values, visited, adjacent, count);
        if (count > n / 2) {
            count = n - count;
            find = !find;
        }
        bool flag = false;
        cout << count << endl;
        for(int i = 0; i < n; i++) {
            if (values[i] == find) {
                if(!flag) flag = true;
                else cout << " ";
                cout << i+1;
            }
        }
        cout << endl;
    }
}