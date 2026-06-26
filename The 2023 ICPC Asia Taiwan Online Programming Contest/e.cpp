#include <bits/stdc++.h>
using namespace std;
using ll = __uint128_t;
using ull = unsigned long long;
unordered_map<ull, ll> f_cache;

ll a, m;

ll f(ull b) {
    if (b == 0) return 2 % m;
    if (b == 1) return a;
    if (f_cache.find(b) != f_cache.end()) return f_cache[b];
    ull b1 = b / 2, b2 = b - b1;
    ull abs_b1_b2 = b1 > b2 ? b1 - b2 : b2 - b1;
    return f_cache[b] = (f(b1) * f(b2) % m + m - f(abs_b1_b2)) % m;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ull b;
    ull aull, mull;
    cin >> aull >> b >> mull;
    a = aull;
    m = mull;
    a %= m;

    cout << (ull) f(b);

    return 0;
}