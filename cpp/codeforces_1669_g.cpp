#include <bits/stdc++.h>
using namespace std;
void solve(vector<string> s, int b) {
    if (s.size() > 1)
    for (int i = s.size() - 2; i >= 0; i--) {
        for (int x = 0; x < b; x++) {
            int previ = i;
            if (s[i][x] == '*') {
                for (int newi = i+1; newi < s.size(); newi++) {
                    if (s[newi][x] == 'o' || s[newi][x] == '*') {
                        break;
                    } else if (s[newi][x] == '.') {
                        s[previ][x] = '.';
                        previ = newi;
                        s[newi][x] = '*';
                    }
                }
            }
        }
    }

    for (int i = 0; i < s.size(); i++) {
        cout << s[i] << "\n";
    }
}
int main() {
    int c; cin >> c;
    for(int i = 0; i < c; i++) {
        int a, b; cin >> a >> b;
        vector<string> s(a);
        for (int k = 0; k < a; k++) {
            cin >> s[k];
        }
        solve(s, b);
    }
}