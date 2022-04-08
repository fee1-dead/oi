#include <bits/stdc++.h>
using namespace std;
int csum[200001], osum[200001], wsum[200001];
int main() {
    string s; cin >> s;
    int len = s.length();
    for (int i = 1; i <= len; i++) {
        csum[i] = csum[i-1];
        osum[i] = osum[i-1];
        wsum[i] = wsum[i-1];
        char c = s[i-1];
        if(c == 'C') csum[i]++;
        else if(c == 'O') osum[i]++;
        else if(c == 'W') wsum[i]++;
        else return 100;
    }
    int q; cin >> q;
    for(int i = 0; i<q; i++) {
        int a, b; cin >> a >> b;
        int cs = csum[b] - csum[a-1];
        int os = osum[b] - osum[a-1];
        int ws = wsum[b] - wsum[a-1];
        bool possible = cs % 2 == 1 && os % 2 == 0 && ws % 2 == 0;
        possible = possible || (cs % 2 == 0 && os % 2 == 1 && ws % 2 == 1);
        if (possible) cout << 'Y';
        else cout << 'N';
    }
    cout << "\n";
}