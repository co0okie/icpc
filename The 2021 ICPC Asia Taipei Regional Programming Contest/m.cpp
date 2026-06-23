#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n, s, f, r;
    cin >> m >> n;
    vector<vector<bool>> mp(m, vector<bool>(n));
    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            bool b; cin >> b;
            mp[x][y] = b;
        }
    }
    cin >> s >> f >> r;
    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            if (mp[x][y] != s) continue;
            bool N = x - 1 < 0 ? 0 : mp[x - 1][y];
            bool S = x + 1 >= m ? 0 : mp[x + 1][y];
            bool W = y - 1 < 0 ? 0 : mp[x][y - 1];
            bool E = y + 1 >= n ? 0 : mp[x][y + 1];
            if (
                N == f && E == r || E == f && S == r ||
                S == f && W == r || W == f && N == r
            ) {
                cout << x << " " << y << "\n";
            }
        }
    }
}