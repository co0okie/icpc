#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    vector<ll> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    vector<ll> gcd_f(n);
    vector<ll> gcd_b(n);
    gcd_f[0] = p[0];
    gcd_b[n - 1] = p[n - 1];
    for (int i = 1; i < n; i++) {
        gcd_f[i] = gcd(gcd_f[i - 1], p[i]);
    }
    for (int i = n - 2; i >= 0; i--) {
        gcd_b[i] = gcd(gcd_b[i + 1], p[i]);
    }
    ll s = gcd_b[0];
    for (int i = 1; i < n - 1; i++) {
        s += min(gcd_f[i], gcd_b[i]);
    }
    cout << s;
}