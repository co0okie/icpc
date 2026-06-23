#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll S;
vector<int> vl;
vector<int> vr;
vector<int> sl;
vector<int> sr;
ll diff;
ll MAX_WEIGHT;
vector<vector<bool>> dpl;
vector<vector<bool>> dpr;
void printDp(const vector<vector<bool>>& dp) {
    for (ll cnt = 0; cnt <= S; cnt++) {
        for (ll w = 0; w <= MAX_WEIGHT; w++) {
            cout << dp[cnt][w] << " ";
        }
        cout << endl;
    }
}
void buildDp(vector<vector<bool>>& dp, const vector<int>& s) {
    dp.resize(S + 1);
    ranges::fill(dp, vector<bool>(MAX_WEIGHT + 1, 0));
    dp[0][0] = 1;
    if (s.empty()) return;
    for (ll i = 0, set_sum = s[i]; i < s.size(); ++i, set_sum += s[i]) {
        // cout << "adding s[" << i << "] = " << s[i] << ", set sum = " << set_sum << endl;
        for (ll cnt = i; cnt >= 0; cnt--) {
            for (ll weight = set_sum - s[i]; weight >= 0; weight--) {
                if (dp[cnt][weight]) {
                    // cout << "dp[" << cnt << "][" << weight << "] => dp[" <<
                    // cnt + 1 << "][" << weight + s[i] << "]" << endl;
                    dp[cnt + 1][weight + s[i]] = 1;
                }
            }
        }
    }
}
void solve() {
    cin >> S;
    vl.resize(S);
    vr.resize(S);
    sl.resize(0);
    sr.resize(0);
    MAX_WEIGHT = S * (S + 1) / 2;
    for (int i = 0; i < S; i++) cin >> vl[i];
    for (int i = 0; i < S; i++) cin >> vr[i];
    diff = 0;
    for (int i = 0; i < S; i++) diff += (vr[i] - vl[i]) * (i + 1);
    // cout << "diff = " << diff << endl;
    if (diff < 0 || diff > 2 * MAX_WEIGHT) {
        cout << -1 << endl;
        return;
    }
    for (int i = 0; i < S; i++) if (vl[i] == 1) sl.push_back(i + 1);
    for (int i = 0; i < S; i++) if (vr[i] == 2) sr.push_back(i + 1);
    buildDp(dpl, sl);
    buildDp(dpr, sr);
    // cout << "left:\n";
    // printDp(dpl);
    // cout << "right:\n";
    // printDp(dpr);
    for (ll cnt = 0; cnt <= S; cnt++) {
        for (ll w1 = max(0ll, diff - MAX_WEIGHT), w2 = diff - w1; 
        w1 <= min(diff, MAX_WEIGHT); w1++, w2--) {
            // 0 <= w2 = diff - w1 <= MAX_WEIGHT
            // diff - MAX_WEIGHT <= w1 <= diff
            // 0 <= w1 <= MAX_WEIGHT
            if (dpl[cnt][w1] && dpr[cnt][w2]) {
                cout << cnt << endl;
                return;
            }
        }
    }
    cout << -1 << endl;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}