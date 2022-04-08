#include <bits/stdc++.h>
using namespace std;
void solve() {
    string s; cin >> s;
    int len = s.length();
    if(len == 1) {
        cout << "1\n"; return;
    } else if (len == 2) {
        cout << ((s[0] == s[1]) ? 0 : 2) << "\n"; return;
    }
    int removed = 0;
    for(int i = 0; i < len; i+=2) {
        if(i == len) { // suggests that string is odd
        // check if we have deleted enough 
            if(removed  )
            removed++;
        } else if (i == len - 2) {

        }
    }
}
int main() {
    int t; cin >> t;
    for(int c = 0; c < t; c++) solve();
}