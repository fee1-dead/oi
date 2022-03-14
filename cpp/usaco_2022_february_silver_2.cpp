#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<ll, ll> insns[45];
bool sel[45];
int variants[45];

int main() {
    int n;
    ll xdest, ydest;
    cin >> n >> xdest >> ydest;

    for (int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        insns[i] = make_pair(x, y);
    }

    while(true) {
        ll x = 0;
        ll y = 0;

        int i = 0;
        while (sel[i] == true) {
            sel[i] = false;
            i++;
            if (i >= n) {
                for (int j = 0; j < n; j++) {
                    cout << variants[j] << endl;
                }
                return 0;
            }
        }
        sel[i] = true;

        int cnt = 0;

        for (int j = 0; j < n; j++) {
            if (sel[j]) {
                cnt++;

                auto insn = insns[j];

                x += insn.first;
                y += insn.second;
            }
        }

        if (x == xdest && y == ydest) {
            variants[cnt-1]++;
        }
    }
}