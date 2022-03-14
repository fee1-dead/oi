#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int t; cin >> t;
    for (int tcase = 0; tcase < t; tcase++) {
        int n; cin >> n;
        vector<int> psum = vector<int>(n+1, 0);
        for (int i = 1; i <= n; i++) {
            char c; cin >> c;
            psum[i] = c - '0';
        }

        for (int i = 1; i <= n; i++) {
            psum[i] += psum[i - 1];
        }

        map<int, ll> freq;

        for (int i = 0; i <= n; i++) {
            freq[psum[i] - i]++;
        }

        ll ans = 0;

        for (auto p: freq) {
            ll f = p.second;
            ans += f*(f-1)/2;
        }
        cout << ans << endl;
    }
}