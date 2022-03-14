#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n,q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll &x: a)
        cin >> x;
    vector<ll> p(n + 1);
    ll accum = 0;
    for (int i = 0; i < n; i++) {
        accum ^= a[i];
        p[i + 1] = accum;
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        cout << (p[r] ^ p[l-1]) << "\n";
    }
}