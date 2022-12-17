#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vi = vector<int>;
vi adj[10005];
vi children[10005];
int level[10005];
bool visited[10005];
void dfs(int node) {
    visited[node] = true;
    for(int adjnode: adj[node]) {
        if(visited[adjnode]) continue;
        children[node].push_back(adjnode);
        dfs(adjnode);
    }
}
typedef struct Level {
    int cur;
    size_t cap;
};
void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0);
    vector<Level> levels;
    levels.push_back(Level { .cur = 0, .cap = 1 });
    level[0] = 0;

    vi cur_set = {0};
    size_t size_of_next_level = children[0].size();
    while (cur_set.size() > 0) {
        if (size_of_next_level > 0) levels.push_back(Level { .cur = 0, .cap = size_of_next_level });
        vi next;
        int sum = 0;
        for(int node: cur_set) {
            for(int child: children[node]) {
                sum += children[child].size();
                next.push_back(child);
            }
        }
        cur_set = next;
        size_of_next_level = sum;
    }
    
    for(int i = 0; i < q; i++) {
        int node; cin >> node;
        for(int l = 0; l < levels.size(); l++) {
            if (levels[l].cur == levels[l].cap) continue;
            levels[l].cur++;
            break;
        }
    }
    int sum = 0;
    for(int l = 0; l < levels.size(); l++) {
        if (levels[l].cur == levels[l].cap) sum += levels[l].cap;
    }
    cout << sum << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases; cin >> cases;
    for(int i = 1; i <= cases; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}