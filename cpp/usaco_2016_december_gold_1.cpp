#include <bits/stdc++.h>
using namespace std;
using ll = long long;
pair<int, int> pos[1000];
ll dist[1000][1000];
int n;
ll first_true(ll min_val, ll max_val, function<bool(ll)> f) {
    while (min_val < max_val) {
        ll mid = min_val + (max_val - min_val) / 2;
        if (f(mid)) {
            max_val = mid;
        } else {
            min_val = mid + 1;
        }
    }
    return min_val;
}

void dfs(vector<bool>& visited, int node, int& total, ll cap) {
    visited[node] = true;
    total += 1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[node][i] <= cap)
            dfs(visited, i, total, cap);
    }
}

bool validate(ll capability) {
    vector<bool> visited(n);
    int total = 0;
    dfs(visited, 0, total, capability);
    return total == n;
}

int main() {
    freopen("moocast.in", "r", stdin); freopen("moocast.out", "w", stdout);
    cin >> n;
    for(int i = 0; i<n; i++) {
        cin >> pos[i].first >> pos[i].second;
    }

    for(int x = 0; x < n; x++) {
        for(int y = 0; y < n; y++) {
            ll xdist = pos[x].first - pos[y].first;
            ll ydist = pos[x].second - pos[y].second;
            ll d = xdist * xdist + ydist * ydist;
            dist[x][y] = d;
        }
    }

    cout << first_true(0, 2e9, validate) << endl;
}