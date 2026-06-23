#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x;
    int y;
};

int n, m, k;
int u1, v1, u2, v2;
vector<Point> stones;
vector<vector<int>> stone_map;

bool solvable(int energy) {
    // cout << "energy " << energy << endl;

    // 0 ~ energy - 1: move, energy ~ k - 1: fix
    for (int j = energy; j < k; j++) {
        auto s = stones[j];
        if (u1 <= s.x && s.x <= u2 && v1 <= s.y && s.y <= v2) {
            // cout << "stone at (" << s.x << ", " << s.y << "), unsolvable" << endl;
            return 0;
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, 0));
    int area = 0;
    int stone_count = 0;
    queue<Point> frontier;
    visited[u1][v1] = 1;
    frontier.push({u1, v1});
    while (!frontier.empty()) {
        auto p = frontier.front();
        frontier.pop();
        // cout << "visit: " << p.x << ", " << p.y << endl;
        if (0 <= stone_map[p.x][p.y] && stone_map[p.x][p.y] < energy) {
            stone_count++;
        }
        area++;

        for (auto [dx, dy] : vector<tuple<int, int>>({{0, 1}, {0, -1}, {1, 0}, {-1, 0}})) {
            Point np({p.x + dx, p.y + dy});
            // cout << "neighbor " << np.x << " " << np.y << endl;
            if (np.x < 0 || np.x >= n || np.y < 0 || np.y >= m) {
                // cout << "out of grid" << endl;
                continue;
            }
            if (stone_map[np.x][np.y] >= energy) {
                // cout << "blocked" << endl;
                continue;
            }
            if (visited[np.x][np.y]) {
                // cout << "visited" << endl;
                continue;
            }
            visited[np.x][np.y] = 1;
            frontier.push(np);
        }
    }

    // cout << "stone count " << stone_count << endl;
    // cout << "area " << area << endl;

    return area - (u2 - u1 + 1) * (v2 - v1 + 1) >= stone_count;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for (int _ = 0; _ < k; _++) {
        int x, y;
        cin >> x >> y;
        stones.push_back({x - 1, y - 1});
    }
    cin >> u1 >> v1 >> u2 >> v2;
    u1--; v1--; u2--; v2--;

    stone_map = vector<vector<int>>(n, vector<int>(m, -1));
    for (int i = 0; i < k; i++) {
        stone_map[stones[i].x][stones[i].y] = i;
    }
    // for (auto row : stone_map) {
    //     for (auto cell : row) {
    //         cout << cell << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    auto it = ranges::partition_point(views::iota(0, (int) stones.size() + 1), [](int i) {
        return !solvable(i);
    });
    if (*it == stones.size() + 1) {
        cout << -1 << "\n";
    } else {
        cout << *it << "\n";
    }
}