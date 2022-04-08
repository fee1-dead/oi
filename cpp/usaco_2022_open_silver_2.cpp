#include <bits/stdc++.h>
using namespace std;

bool works[18][18];

int main() {
    string s, t; cin >> s >> t;
    int slength = s.length();
    int tlength = t.length();

    for(char c1 = 'a'; c1 <= 'r'; c1++) {
        int node1 = c1 - 'a';
        for(char c2 = 'a'; c2 <= 'r'; c2++) {
            int node2 = c2 - 'a';
            int ti = 0;
            int si = 0;
            bool failure = false;

            while(ti < tlength && si < slength) {
                while(ti < tlength) {
                    if(t[ti] == c1 || t[ti] == c2) break;
                    else ti++;
                }
                while(si < slength) {
                    if(s[si] == c1 || s[si] == c2) break;
                    else si++;
                }
                if (si == slength && ti == tlength) {
                    break;
                } else if (si == slength || ti == tlength) {
                    failure = true;
                    break;
                } else if (s[si] != t[ti]) {
                    failure = true;
                    break;
                } else {
                    si++; ti++;
                }
            }

            if (!(si == slength && ti == tlength) && (si == slength || ti == tlength)) {
                failure = true;
            } 

            if(!failure) {
                works[node1][node2] = true;
                works[node2][node1] = true;
            }
        }
    }
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        string qs; cin >> qs;
        int qlen = qs.length();
        bool bad = false;
        for(int a = 0; a < qlen; a++) {
            for(int b = 0; b < qlen; b++) {
                if(!works[qs[a] - 'a'][qs[b] - 'a']) {
                    bad = true;
                    break;
                }
            }
            if(bad) break;
        }
        cout << (bad?"N":"Y");
    }
    cout << '\n';
}