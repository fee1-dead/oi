#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll raw[100005], pgcd[100005], sgcd[100005];
int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> raw[i];

    for (int i = 1; i <= n; i++) {
        pgcd[i] = gcd(pgcd[i-1], raw[i]);
    }

    for (int i = n; i >= 1; i--) {
        sgcd[i] = gcd(sgcd[i+1], raw[i]);
    }

    ll res = 0;

    for (int i = 1; i <= n; i++) {
        ll ans = gcd(pgcd[i-1], sgcd[i+1]);
        res = max(ans, res);
    }

    cout << res << endl;
}