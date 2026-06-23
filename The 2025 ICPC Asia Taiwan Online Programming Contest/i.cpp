#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n, q;

vector<ll> p; // pressure limit
vector<ll> s; // current pressure
vector<ll> v; // vent count
vector<ll> oc; // p == 1 count
vector<ll> ac; // add count

ll build(ll L, ll R) {
    // cout << "build [" << l << ", " << r << "]" << endl;
    ll i = (L + R) | (L != R);
    s[i] = 0;
    v[i] = 0;
    ac[i] = 0;
    
    if (L == R) {
        // cout << "leaf" << endl;
        cin >> p[i];
        oc[i] = p[i] == 1;
        // cout << "[" << l << ", " << r << "]: " << p[i] << endl;
        return i;
    }

    ll M = (L + R) / 2;
    ll i1 = build(L, M);
    ll i2 = build(M + 1, R);

    p[i] = p[i1] == 1 ? p[i2] - s[i2] : p[i2] == 1 ? p[i1] - s[i1] : 
        min(p[i1] - s[i1], p[i2] - s[i2]);
    oc[i] = oc[i1] + oc[i2];
    // cout << "[" << l << ", " << r << "]: " << p[i] << endl;

    return i;
}

// [L, R]: segment interval, [l, r]: add interval
// K: segment increment, k: add interval increment
// AC: add count, adc: add interval add count
ll add(ll L, ll R, ll l, ll r, ll K, ll k, ll AC, ll adc) {
    ll i = (L + R) | (L != R);
    // cout << "[" << L << ", " << R << "]: K=" << K << ", AC=" << AC
    // << ", [" << l << ", " << r << "]: k=" << k << ", adc=" << adc << ", ";
    // cout << "p=" << p[i] << ", s=" << s[i] << ", ac=" << ac[i] << ", v=" << v[i] << ", oc=" << oc[i] << endl;
    if (l <= L && R <= r && (K + k < p[i] - s[i] || R - L + 1 == oc[i])) {
        if (R - L + 1 == oc[i]) s[i] = 0; else s[i] += K + k;
        v[i] += oc[i] * (AC + adc);
        ac[i] += AC + adc;
        // cout << "lazy p=" << p[i] << ", s=" << s[i] << ", ac=" << ac[i] << ", v=" << v[i] << ", oc=" << oc[i] << endl;
        return i;
    }

    if (L == R) {
        // cout << "leaf (p, s, v) = (" << p[i] << ", " << s[i] << ", " << v[i] << ")";
        if (p[i] == 1) {
            v[i] += AC + adc;
        } else {
            p[i] = max(p[i] / 2, 1ll);
            v[i]++;
        }
        s[i] = 0;
        oc[i] = p[i] == 1;
        // cout << " -> (" << p[i] << ", " << s[i] << ", " << v[i] << ")" << endl;
        return i;
    }

    ll M = (L + R) / 2, i1, i2;
    if (l <= M) i1 = add(L, M, l, r, K + s[i], k, AC + ac[i], adc);
    else i1 = add(L, M, L, M, K + s[i], 0, AC + ac[i], 0);
    if (r > M) i2 = add(M + 1, R, l, r, K + s[i], k, AC + ac[i], adc);
    else i2 = add(M + 1, R, M + 1, R, K + s[i], 0, AC + ac[i], 0);
    
    // cout << "[" << L << ", " << R << "]: (p, s, ac, v, oc) = (" 
    //     << p[i] << ", " << s[i] << ", " << ac[i] << ", " << v[i] << ", " << oc[i] << ")";
    bool all_one1 = M - L + 1 == oc[i1], all_one2 = R - M == oc[i2];
    p[i] = all_one1 ? p[i2] - s[i2] : all_one2 ? p[i1] - s[i1] : 
        min(p[i1] - s[i1], p[i2] - s[i2]);
    s[i] = 0;
    ac[i] = 0;
    v[i] = v[i1] + v[i2];
    oc[i] = oc[i1] + oc[i2];
    // cout << " -> (" << p[i] << ", " << s[i] << ", " << ac[i] << ", " << v[i] << ", " << oc[i] << ")" << endl;

    return i;
}

ll count_vent(ll L, ll R, ll l, ll r) {
    ll i = (L + R) | (L != R);
    if (l <= L && R <= r) {
        return v[i];
    }

    ll M = (L + R) / 2;
    ll i1 = add(L, M, L, M, 0, 0, ac[i], 0);
    ll i2 = add(M + 1, R, M + 1, R, 0, 0, ac[i], 0);
    ac[i] = 0;
    v[i] = v[i1] + v[i2];

    ll s = 0;
    if (l <= M) s += count_vent(L, M, l, r);
    if (M < r) s += count_vent(M + 1, R, l, r); 
    return s;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q;
    p.resize(2 * n);
    s.resize(2 * n);
    v.resize(2 * n);
    ac.reserve(2 * n);
    oc.resize(2 * n);

    build(0, n - 1);

    for (;q--;) {
        ll op, l, r, k;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> k;
            // cout << "op add [" << l - 1 << ", " << r - 1 << "]: " << k << endl;
            add(0, n - 1, l - 1, r - 1, 0, k, 0, 1);
        } else if (op == 2) {
            cin >> l >> r;
            cout << count_vent(0, n - 1, l - 1, r - 1) << endl;
        }
    }
}