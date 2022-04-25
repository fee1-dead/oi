#include <bits/stdc++.h>
using namespace std;
void solve(vector<int> v) {
    int prev = -1;
    int totaldiff = 0;
    for (int elem: v) {
        if (prev != -1) {
            if (elem - prev > 1) {
                totaldiff += elem - prev - 1;
                if (totaldiff > 2) {
                    cout << "no\n";
                    return;
                }
            }
        }
        prev = elem;
    }
    if (totaldiff > 2) {
                    cout << "no\n";
                    
                } else {
                    cout << "yes\n";
                }
}
int main() {
    int c; cin >> c;
    for (int i = 0; i < c; i++) {
        int n; cin >> n;
        vector<int> v(n);
        for(int k = 0; k < n;k++) {
            cin >> v[k];
        }
        solve(v);
    }
}