#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    string w;
    cin >> w;

    vector<vector<int>> dp(w.size(), vector<int>(w.size(), 0));
    for (int i = 1; i < w.size(); i++) {
        dp[i - 1][i] = w[i - 1] == w[i] ? 0 : 1;
    }

    for (int i = 2; i < w.size(); i++) {
        for (int j = i; j < w.size(); j++) {
            dp[j - i][j] = w[j - i] == w[j] ? dp[j - i + 1][j - 1] :
                min({dp[j - i][j - 1], dp[j - i + 1][j], dp[j - i + 1][j - 1]}) + 1;
        }
    }

    // for (auto v : dp) {
    //     for (auto i : v) {
    //         cout << i << " ";
    //     }
    //     cout << "\n";
    // }

    cout << dp[0][w.size() - 1] << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;

    for (int _ = 0; _ < t; _++) {
        solve();
    }
}