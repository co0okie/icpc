#include <bits/stdc++.h>
using namespace std;

int n, x, y;

int ring_size;

vector<list<int>> adj;

// sub tree -> attr
vector<int> root;
vector<int> height;
vector<int> diameter;

template <template <typename...> class Container, class... T>
ostream& operator<<(ostream& os, const Container<T...>& container) {
    os << "[";
    for (auto it = container.begin(); it != container.end(); it++) {
        if (it != container.begin()) os << ", ";
        os << *it;
    }
    return os << "]";
}

auto pathToY(int u, int u_prev) {
    if (u == y) return vector<int>({y});
    for (auto v : adj[u]) {
        if (v == u_prev) continue;
        auto path = pathToY(v, u);
        if (path.empty()) continue;
        path.push_back(u);
        return path;
    }
    return vector<int>();
}

int neighbor1;
int neighbor2;
int max_diameter;
int heightDiameter(int u, int u_prev) {
    auto max_h1 = -1, max_h2 = -1;
    for (auto v : adj[u]) {
        if (v == u_prev || v == neighbor1 || v == neighbor2) continue;
        auto h = heightDiameter(v, u);
        if (h > max_h1) tie(max_h1, max_h2) = make_pair(h, max_h1); 
        else if (h > max_h2) max_h2 = h;
    }
    auto d = max_h1 + max_h2 + 2;
    if (d > max_diameter) max_diameter = d;
    return max_h1 + 1;
}

void solve() {
    cin >> n >> x >> y;
    x--, y--;
    adj.clear();
    adj.resize(n);
    for (int _ = n - 1; _--;) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // cout << "adj = " << adj << endl;
    root = pathToY(x, -1);
    root.erase(root.begin());
    // cout << x << " to " << y << ": " << root << endl;
    height.resize(root.size());
    diameter.resize(root.size());
    adj[x].insert(adj[x].end(), adj[y].begin(), adj[y].end());
    for (auto u : adj[y]) {
        ranges::replace(adj[u], y, x);
    }
    adj[y].clear();
    // cout << "adj = " << adj << endl;
    for (int i = 0; i < root.size(); i++) {
        auto s = root[i];
        neighbor1 = root[i == 0 ? root.size() - 1 : i - 1];
        neighbor2 = root[(i + 1) % root.size()];
        // cout << "s = " << s << endl;
        // cout << "neighbor = " << neighbor.first << " " << neighbor.second << endl;
        // cout << "adj = " << adj << endl;

        max_diameter = 0;
        height[i] = heightDiameter(s, -1);
        diameter[i] = max_diameter;
    }
    // cout << "height = " << height << endl;
    // cout << "diameter = " << diameter << endl;
    // cout << "adj = " << adj << endl;
    
    if (root.size() == 1) {
        cout << 2 * (n - 2) - diameter[0] << endl;
        return;
    }

    
    auto min_cost = 2 * n;
    
    auto max_d = INT_MIN;
    auto max_h_minus_j = INT_MIN;
    auto max_h_plus_j = INT_MIN;
    for (int i = 0; i < root.size(); i++) {
        if (i > 0) {
            max_d = max({max_d, 
                height[i] + i + max_h_minus_j, 
                height[i] - i + max_h_plus_j + (int)root.size()
            });
        }
        max_h_minus_j = max(max_h_minus_j, height[i] - i);
        max_h_plus_j = max(max_h_plus_j, height[i] + i);
    }
    min_cost = min(min_cost, 2 * (n - 1) - 2 - max_d);

    for (int i = 0; i < root.size(); i++) {
        auto cost = 2 * (n - 1) - root.size() - diameter[i];
        if (cost < min_cost) min_cost = cost;
    }
    cout << min_cost << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; 
    cin >> t;
    while (t--) solve();
}