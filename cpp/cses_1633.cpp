#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n; cin >> n;
    vector<ll> v(n+1);
    v[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 6; j++) {
            if (i - j >= 0) {
                v[i] += v[i - j];
            }
        }
        v[i] %= 1000000007;
    }
    cout << v[n] << "\n";
}