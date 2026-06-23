#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
T bestChar(T sl, T tl, T sr, T tr) {
    array<T, 4> arr({sl, tl, sr, tr});
    ranges::sort(arr);
    return (arr[1] + arr[2]) / 2;
    // auto [minl, maxl] = minmax(sl, tl);
    // auto [minr, maxr] = minmax(sr, tr);
    // if (minl >= maxr) {
    //     return (minl + maxr) / 2;
    // } else if (minr >= maxl) {
    //     return (minr + maxl) / 2;
    // } else {
    //     auto top = min(maxr, maxl);
    //     auto bottom = max(minr, minl);
    //     return (top + bottom) / 2;
    // }
}

int main() {
    ll n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    string out;
    out.resize(n);
    for (ll i = 0; i < ((n + 1) / 2); i++) {
        ll j = n - 1 - i;
        out[i] = out[j] = bestChar(s[i], t[i], s[j], t[j]);
    }
    cout << out;
}