#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define INF 100001
bool le(const string& sa, int ai, int al, const string& sb, int bi, int bl) {
    if (al < bl) return true;
    if (al > bl) return false;
    for (int i = 0; i < al; i++) {
        if (sa[ai + i] < sb[bi + i]) return 1;
        if (sa[ai + i] > sb[bi + i]) return 0;
    }
    return 1;
}
void print(vector<vector<int>>& dp) {
    for (int l = 1; l < dp[0].size(); l++) {
        for (int i = 0; i < dp.size(); i++) {
            if (dp[i][l] < INF) {
                printf("%3d ", dp[i][l]);
            } else {
                printf("INF ");
            }
        }
        cout << endl;
    }
}
int main() {
    string x;
    string b;
    cin >> x >> b;
    if (x == "0") {
        cout << 0;
        return 0;
    }

    vector<vector<int>> dp(x.size()); // dp[i][l], min comma count if cut at x.substr(i, i + l)
    for (auto& y : dp) {
        y.resize(b.size() + 1, INF);
    }

    if (dp.size()) for (int l = 1; l < dp[0].size(); l++) {
        dp[0][l] = 0; // head
    }

    // cout << "dp init" << endl;
    // print(dp);

    for (int i = 1; i < dp.size(); i++) {
        int min_comma = INF;
        for (int l = 1; l < dp[i].size(); l++) {
            if (i + l > x.size()) {
                dp[i][l] = INF;
                break;
            }
            if (x[i] == '0') { // cannot add comma before '0'
                dp[i][l] = INF;
                continue;
            }
            int old_min_comma = min_comma;
            if (i - l >= 0) min_comma = min(min_comma, dp[i - l][l]);
            if (i - l >= 0 && le(x, i - l, l, x, i, l)) {
                dp[i][l] = min_comma + 1;
            } else {
                dp[i][l] = old_min_comma + 1;
            }
        }
    }

    // cout << "after dp build" << endl;
    // print(dp);

    int min_comma = INF;
    for (int l = 1; l < dp[0].size(); l++) {
        ll i = x.size() - l;
        if (le(x, i, l, b, 0, b.size())) {
            min_comma = min(min_comma, dp[i][l]);
        }
    }
    if (min_comma < INF) {
        cout << min_comma;
    } else {
        cout << "NO WAY";
    }

    return 0;
}