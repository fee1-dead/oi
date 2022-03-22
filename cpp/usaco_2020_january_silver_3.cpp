#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
int locations[100001];
int location_to_cow_number[100001];
vector<pair<ll, int>> adj[100001];

bool total_visited[100001];
bool visited_positions[100001];
vector<int> visited_cows;

ll last_true(ll minval, ll maxval, function<bool(ll)> f) {
    minval--;
    while (minval < maxval) {
        ll mid = minval + (maxval - minval + 1) / 2;
        if (f(mid)) {
            minval = mid;
        } else {
            maxval = mid - 1;
        }
    }
    return minval;
}

void dfs(int node, ll minwidth) {
    int location = locations[node];
    visited_cows.push_back(node);
    visited_positions[location] = true;
    total_visited[node] = true;
    for (auto wormhole: adj[location]) {
        if (wormhole.first < minwidth) continue;
        int adjacent_cow = location_to_cow_number[wormhole.second];
        if (total_visited[adjacent_cow]) continue;
        dfs(adjacent_cow, minwidth);
    }
}

bool validate(ll minwidth) {
    fill(total_visited, end(total_visited), false);
    for(int i = 1; i <= n; i++) {
        if (!total_visited[i]) {
            fill(visited_positions, end(visited_positions), false);
            visited_cows.clear(); 
            dfs(i, minwidth);
            for(auto node: visited_cows) {
                if (!visited_positions[node]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    freopen("wormsort.in", "r", stdin); freopen("wormsort.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int loc;
        cin >> loc;
        locations[i] = loc;
        location_to_cow_number[loc] = i;
    }
    for (int i = 0; i < m; i++) {
        int a, b; ll w;
        cin >> a >> b >> w;
        adj[a].push_back({w, b});
        adj[b].push_back({w, a});
    }
    if (validate(LLONG_MAX)) {
        cout << "-1" << endl;
    } else {
        cout << last_true(0, 1e9 + 5, validate) << endl;
    }
}