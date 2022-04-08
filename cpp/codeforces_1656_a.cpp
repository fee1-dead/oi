#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    for(int i = 0; i < t; i++) {
        int n; cin >> n;
        pair<int, int> min = {INT_MAX, 0};
        pair<int, int> max = {INT_MIN, 0};
        for(int j = 1; j <= n; j++) {
            ll num; cin >> num;
            if (num < min.first) {
                min = {num, j};
            }
            if (num > max.first) {
                max = {num, j};
            }
        }
        cout << min.second << " " << max.second << "\n";
    }
}