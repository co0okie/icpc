#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, m, g;
int xs, ys;
struct Point {int x, y;};
vector<vector<int>> alt;
vector<vector<Point>> guard;
vector<vector<ll>> turn;
// check t and t+1
bool hasGuard(int x, int y, ll t) {
    for (auto& gd : guard) {
        auto s1 = t % gd.size(), s2 = (t + 1) % gd.size();
        if (gd[s1].x == x && gd[s1].y == y || gd[s2].x == x && gd[s2].y == y) {
            return 1;
        }
    }
    return 0;
}
void solve() {
    cin >> n >> m;
    alt.assign(n, vector<int>(m));
    turn.assign(n, vector<ll>(LONG_LONG_MAX));
    for (int y = 0; y < m; y++) {
        for (int x = 0; x < n; x++) {
            cin >> alt[x][y];
        }
    }
    cin >> xs >> ys >> g;
    guard.clear();
    for (int i = 0; i < g; i++) {
        int s; cin >> s;
        guard.push_back(vector<Point>(s));
        for (int j = 0; j < s; j++) {
            cin >> guard[i][j].x >> guard[i][j].y;
        }
    }

    // pair<turn, node>
    priority_queue<pair<ll, Point>, vector<pair<ll, Point>>, greater<pair<ll, Point>>> frontier;
    vector<vector<bool>> visited(n, vector<bool>(m, 0));
    frontier.push({0ll, {xs, ys}});
    while (!frontier.empty()) {
        auto [x, y] = frontier.top().second;
        if (visited[x][y]) continue;
        visited[x][y] = 1;
        for (auto [x2, y2] : vector<Point>{{x+1,y}, {x-1,y}, {x,y+1}, {x,y-1}}) {
            
        }
    }
}
int main() {
    ll T; cin >> T;
    while (T--) solve();
}