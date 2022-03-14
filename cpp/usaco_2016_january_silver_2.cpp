#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int min_idx[7], max_idx[7];
int main() {
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);

    int n; cin >> n;

    int prefix = 0;
    for (int i = 1; i <= n; i++) {
        int val; cin >> val;
        prefix += val;
        prefix %= 7;

        if (min_idx[prefix] == 0) {
            min_idx[prefix] = i;
        }

        max_idx[prefix] = i; 
    }

    int ans = 0;
    for (int i = 0; i < 7; i++) {
        ans = max(ans, max_idx[i] - min_idx[i]);
    }
    cout << ans << endl;
}