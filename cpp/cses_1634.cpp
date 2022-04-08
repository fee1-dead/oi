#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll dp[1000001];
int coins[100];
int main() {
    int n, x; cin >> n >> x;
    for (int i = 0; i < n; i++)
        cin >> coins[i];
    for (int i = 1; i <= x; i++) {
        ll m = LLONG_MAX;
        for (int j = 0; j < n; j++) {
            if (coins[j] > i) continue;
            if (dp[i - coins[j]] == LLONG_MAX) continue;
            m = min(dp[i - coins[j]] + 1, m);
        }
        dp[i] = m;
    }
    
    cout << (dp[x] == LLONG_MAX ? -1 : dp[x]) << "\n";
}