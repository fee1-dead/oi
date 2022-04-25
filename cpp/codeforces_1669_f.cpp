#include <bits/stdc++.h>
using namespace std;
void solve(vector<int> v, int n) {
    unordered_map<int, int> bob;
    int sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        sum += v[i];
        int eaten = n - i;
        bob[sum] = eaten;
    }

    int maxv = 0;
    sum = 0;
    for (int i = 0; i < n; i++) {
        sum += v[i];
        int aliceeaten = i + 1;
        if (bob.find(sum) != bob.end()) {
            int bobeaten = bob[sum];
            if (bobeaten + aliceeaten <= n) {
                int eaten = bobeaten + aliceeaten;
                maxv = max(maxv, eaten);
            }
        }
    }
    cout << maxv << "\n";
}
int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        int n; cin >> n;
        vector<int> v(n);
        for(int k = 0; k < n; k++) {
            cin >> v[k];
        }
        solve(v, n);
    }
}