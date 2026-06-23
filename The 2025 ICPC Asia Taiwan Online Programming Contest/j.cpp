#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, k, d;

vector<vector<int>> adj;
vector<vector<int>> len;

int station_count;
int dfs(int u, int s) {
    if (adj[u].size() == 1 && adj[u][0] == s) return 0;
    int max1 = 0, max2 = 0;
    for (int i = 0; i < adj[u].size(); i++) {
        auto v = adj[u][i];
        if (v == s) continue;
        if (d < len[u][i]) {
            station_count = k + 1;
            return LONG_LONG_MAX;
        }
        auto l = dfs(v, u);
        // cout << "dfs(" << v << ") = " << l << endl;
        if (station_count > k) return LONG_LONG_MAX;
        int d_ = len[u][i] + l;
        // cout << u << " -> " << v << ": " << d_ << endl;
        if (d < d_) {
            // cout << "placing station at " << v << endl;
            station_count++;
            d_ = len[u][i];
        }
        if (d_ > max1) tie(max1, max2) = make_pair(d_, max1);
        else if (d_ > max2) max2 = d_;
    }
    if (max2 != 0 && max1 + max2 > d) {
        // cout << "placing station at " << u << endl;
        station_count++;
        return 0;
    }
    return max1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;

    adj.resize(n);
    len.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v, l; cin >> u >> v >> l;
        u--, v--;
        adj[u].push_back(v);
        len[u].push_back(l);
        adj[v].push_back(u);
        len[v].push_back(l);
    }

    int max_d = 0;
    for (auto& e : len) for (auto l : e) max_d += l;

    d = *ranges::partition_point(views::iota(0ll, max_d), [&](auto d_) {
        d = d_;
        station_count = 0;
        dfs(0, -1);
        // cout << "d = " << d << ", k = " << station_count << endl;
        return station_count > k;
    });
    cout << d << endl;
}