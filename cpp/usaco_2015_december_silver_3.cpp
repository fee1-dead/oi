#include <bits/stdc++.h>
using namespace std;

int raw[100005];
int psum[100005][3];

int main() {
    freopen("bcount.in", "r", stdin); freopen("bcount.out", "w", stdout);
    int n, q; cin >> n >> q;

    for (int i = 0; i < n; i++) {
        cin >> raw[i];
        raw[i]--;
    }

    int sum[3] = {0};
    for (int i = 1; i <= n; i++) {
        sum[raw[i - 1]]++;
        memcpy(psum[i], sum, 3 * sizeof(int));
    }

    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        
        for (int j = 0; j < 3; j++) {
            if (j) cout << " ";
            cout << (psum[b][j] - psum[a-1][j]);
        }
        cout << endl;
    }
}