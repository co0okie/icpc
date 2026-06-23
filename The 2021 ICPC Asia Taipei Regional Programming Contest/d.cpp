#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int D, K;

// visited -> dead route, not visited yet -> ?
vector<vector<bool>> visited;
vector<int> digits;

ll tenth[16];

optional<list<char>> dp(int r, uint16_t mask, int scale) {
    // cout << "dp(" << int(r) << ", " << bitset<16>(mask) << ", " << int(scale) << ")" << endl;
    if (mask == 0) { // empty set, scale == -1
        if (r == 0) {
            // cout << "empty valid" << endl;
            return list<char>();
        }
        else {
            // cout << "empty invalid" << endl;
            return nullopt;
        }
    }
    if (visited[r][mask]) {
        // cout << "dead route" << endl;
        return nullopt;
    }
    for (int i = 0; i < D; i++) {
        if (!(mask & (1 << i))) continue;
        // cout << "dp(" << int(r) << ", " << bitset<16>(mask) << ", " << int(scale) << "): " << digits[i] << endl;
        int r1 = (digits[i] * tenth[scale]) % K;
        int r2 = (r + K - r1) % K;
        auto sol = dp(r2, mask ^ (1 << i), scale - 1);
        if (sol) {
            sol->push_front(digits[i]);
            return sol;
        }
    }
    visited[r][mask] = 1;
    return nullopt;
}

int main() {
    cin >> D >> K;
    digits.resize(D);
    for (int i = 0; i < D; i++) {
        cin >> digits[i];
    }
    sort(digits.rbegin(), digits.rend());
    visited.resize(K);
    fill(visited.begin(), visited.end(), vector<bool>(1 << D, 0));
    for (uint64_t i = 0, ten = 1; i < 16; i++, ten *= 10) {
        tenth[i] = ten % K;
    }
    for (int r = K - 1; r >= 0; r--) {
        auto sol = dp(r, (1 << D) - 1, D - 1);
        if (sol) {
            for (auto i : *sol) {
                cout << int(i);
            }
            break;
        }
    }
}