#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t, n, S, p;
    cin >> t;
    while (t--) {
        cin >> n >> S >> p;
        string s;
        getline(cin, s);
        getline(cin, s);
        cout << 2 * ((n - 1) * (n + p - S - 2) + (n - p) * p) << endl;
    }
}