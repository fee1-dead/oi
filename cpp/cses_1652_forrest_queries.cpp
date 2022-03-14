#include <bits/stdc++.h>
using namespace std;
int forr[1001][1001];
int main() {
    int n,q; cin >> n >> q;
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            char c; cin >> c;
            if (c == '*') {
                forr[x][y] = 1;
            }
        }
    }

    for (int y = 1; y <= n; y++) {
        for (int x = 1; x <= n; x++) {
            forr[x][y] += forr[x-1][y];
            forr[x][y] += forr[x][y-1];
            forr[x][y] -= forr[x-1][y-1];
        }
    }

    for (int i = 0; i < q; i++) {
        int y1,x1,y2,x2;
        cin >> x1 >> y1 >> x2 >> y2;
        int ans = 0;
        ans += forr[x2][y2];
        ans += forr[x1-1][y1-1];
        ans -= forr[x2][y1-1];
        ans -= forr[x1-1][y2];
        cout << ans << endl;
    }
}