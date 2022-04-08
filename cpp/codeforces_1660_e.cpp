#include <bits/stdc++.h>
using namespace std;
void solve();
int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) solve();
}

void solve() {
    int n; cin >> n;
    int sum = 0;
    bool matrix[2000][2000];
    for(int y = 0; y < n; y++) 
    for(int x = 0; x < n; x++) {
        char c; cin >> c;
        if (c == '0') matrix[x][y] = 0;
        else if (c == '1') {
            matrix[x][y] = 1; sum++;
        }
        else abort();
    }
    int mincost = INT_MAX;
    for(int start = 0; start < n; start++) {
        int x = start;
        int y = 0;
        int cnt = 0;
        int cost = 0;
        while (y < n) {
            if(matrix[x][y]) cnt++; else cost++;
            if(x == n-1) x = 0;
            else x++;
            y++;
        }
        cost += (sum - cnt);
        mincost = min(mincost, cost);
    }
    cout << mincost << "\n";
}