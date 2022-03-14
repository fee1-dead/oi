#include <bits/stdc++.h>
using namespace std;
int psum[100005];
int main() {
    freopen("maxcross.in", "r", stdin); freopen("maxcross.out", "w", stdout);
    int n, k, b; cin >> n >> k >> b;
    for (int i = 0; i < b; i++) {
        int sig; cin >> sig; psum[sig] = true;
    }
    for (int i = 1; i <= n; i++) {
        psum[i] += psum[i-1];
    }
    int min_borked = INT_MAX;
    for (int i = 0; i <= n - k; i++) {
        min_borked = min(psum[i + k] - psum[i], min_borked);
    }
    cout << min_borked << endl;
}