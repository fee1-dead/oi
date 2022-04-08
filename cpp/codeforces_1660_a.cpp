#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) {
        int a, b; cin >> a >> b;
        if (!a) {
            cout << "1\n";
        } else cout << b * 2 + a + 1 << "\n";
    }
}