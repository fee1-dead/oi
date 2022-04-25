#include <bits/stdc++.h>
using namespace std;
void solve(string s) {
    char lastchar = ' ';
    int count = 0;
    for (char c: s) {
        if (lastchar != c) {
            if (lastchar != ' ') {
                if (count < 2) {
                    cout << "no\n";
                    return;
                }
            }
            count = 1;
            lastchar = c;
        } else {
            count += 1;
        }
    }
    if (count < 2)
        cout << "no\n";
    else cout <<"yes\n";
}
int main() {
    int c; cin >> c;
    for (int i = 0; i < c; i++) {
        string s; cin >> s;
        solve(s);
    }
}