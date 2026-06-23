#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> prod(n);
    vector<list<ll>> adj(n);
    for (int i = 0; i < n; i++) {
        cin >> prod[i];
        prod[i]--;
    }
    for (int i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    deque<ll> q(1, 0);
    vector<ll> dist(n, -1);
    vector<ll> max_d(k, -1);
    dist[0] = 0;
    while (!q.empty()) {
        auto u = q.front(); q.pop_front();
        if (dist[u] > max_d[prod[u]]) max_d[prod[u]] = dist[u];
        for (auto s : adj[u]) {
            if (dist[s] != -1) continue;
            dist[s] = dist[u] + 1;
            q.push_back(s);
        }
    }
    for (int i = 0; i < k; i++) cout << max_d[i] << " ";
}