#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;

int main() {
    ll n, T;
    cin >> n >> T;
    vector<ll> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    ll maxA = *max_element(A.begin(), A.end());
    ll sumAoverT = 0;
    for (auto a : A) sumAoverT += a;
    sumAoverT /= T;

    auto d = *ranges::partition_point(views::iota(1ull, maxA + 1), [&](ll d) {
        ll s = 0;
        for (auto a : A) s += (ll)ceil(double(a) / d);
        // cout << d << " " << s << endl;
        return s > T;
    });
    cout << d;
}