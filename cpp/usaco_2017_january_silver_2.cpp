#include <bits/stdc++.h>
using namespace std;

int raw[100005];
int psum[100005][3];

int main() {
    freopen("hps.in", "r", stdin); freopen("hps.out", "w", stdout);
    int n; cin >> n;
    for (int i = 1; i<=n; i++) {
        char c; cin >> c;
        int num;

        if (c == 'H') num = 0;
        else if (c == 'P') num = 1;
        else num = 2;

        raw[i] = num;
    }
    for (int i = 1; i<=n; i++) {
        int num = raw[i];

        for (int j = 0; j<3; j++) {
            if (j == num) psum[i][j] = psum[i-1][j] + 1;
            else psum[i][j] = psum[i-1][j];
        }
    }

    int maxWins = 0;
    for (int i = 1; i<=n; i++) {
        for (int x = 0; x<3; x++) {
            for (int y = 0; y<3; y++) {
                int gamesWinned = psum[i][x] + psum[n][y] - psum[i][y];
                maxWins = max(gamesWinned, maxWins);
            }
        }
    }

    cout << maxWins << endl;
}