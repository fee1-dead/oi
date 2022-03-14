#include <bits/stdc++.h>
using namespace std;

int raw[200000];
int smod[200001];
int freq[2019];
int main() {
    string s;
    cin >> s;
    size_t n = s.length();
    for (size_t i = 0; i < n; i++) {
        char c = s[i];
        raw[i] = c - '0';
    }

    int factor = 1;
    for (size_t i = n; i >= 1; i--) {
        
        smod[i] = (smod[i+1] + raw[i-1] * factor) % 2019; 

        factor *= 10;
        factor %= 2019;
    }

    for (size_t i = 1; i <= n + 1; i++) {
        freq[smod[i]]++;
    }

    long long ans = 0;
    for (int f: freq) {
        ans += (f * (f - 1)) / 2;
    }

    cout << ans << endl;
}