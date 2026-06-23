#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    vector<tuple<ll, ll, ll>> tunnels;
    ll n, m;
    cin >> n >> m;
    for (ll _ = 0; _ < m; _++) {
        ll s1, s2, v;
        cin >> s1 >> s2 >> v;
        tunnels.push_back({s1 - 1, s2 - 1, v});
    }

    vector<ll> shafts(n, 0); // values

    for (auto [s1, s2, v] : tunnels) {
        shafts[s1] += v;
        shafts[s2] += v;
        swap(shafts[s1], shafts[s2]);
    }

    auto it = max_element(shafts.begin(), shafts.end());

    cout << *it << endl;
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