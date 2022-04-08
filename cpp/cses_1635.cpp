#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, x; cin >> n >> x;
    vector<ll> values(n);
    for (int i = 0; i < n; i++) cin >> values[i];
    vector<ll> dp(x+1);
    dp[0] = 1;
    for(int i = 1; i <= x; i++) {
        for (ll val: values) {
            if (i >= val) {
                dp[i] += dp[i - val];
                dp[i] %= 1000000007;
            }
        }
    }
    cout << dp[x] << "\n";
}