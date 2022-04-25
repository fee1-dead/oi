#include <bits/stdc++.h>
using namespace std;
void solve() {
    cout << "00110011\n";
    while (1) {
        vector<bool> storage(8, false);
        int ones;
        cin >> ones;

        if (ones == 0) {
            break;
        } else if (ones == 8) {
            cout << "11111111\n";
            continue;
        }

        if (ones == -1) {
            abort();
        }

        int bits = abs(ones - 4);
        if (bits == 0) bits = 4;
        while (bits) {
            int bit = rand() % 8;
            while(storage[bit]) {
                bit = rand() % 8;
            }
            storage[bit] = true;
            bits--;
        }
        for (auto b: storage) {
            cout << (b?"1":"0");
        }
        cout << "\n";
    }
}
int main() {
    int cases; cin >> cases;
    for(int i = 0; i < cases; i++) {
        solve();
    }
}