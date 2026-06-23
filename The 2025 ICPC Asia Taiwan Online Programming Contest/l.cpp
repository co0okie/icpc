#include <bits/stdc++.h>
using namespace std;
#define ll long long

using Complex = complex<ll>;

auto cross(Complex z1, Complex z2) {
    return imag(conj(z1) * z2);
}

int orient(Complex z1, Complex z2, Complex z3) {
    auto c = cross(z2 - z1, z3 - z2);
    return c == 0 ? 0 : c > 0 ? 1 : -1;
}

bool between(Complex a, Complex x, Complex b) {
    auto [r1, r2] = minmax(real(a), real(b));
    auto [i1, i2] = minmax(imag(a), imag(b));
    return r1 <= real(x) && real(x) <= r2
        && i1 <= imag(x) && imag(x) <= i2;
}

bool intersect(Complex z1, Complex z2, Complex z3, Complex z4) {
    auto o1 = orient(z1, z2, z3);
    auto o2 = orient(z1, z2, z4);
    auto o3 = orient(z3, z4, z1);
    auto o4 = orient(z3, z4, z2);
    if (o1 != o2 && o3 != o4) return 1;
    if (o1 == 0 && between(z1, z3, z2)) return 1;
    if (o2 == 0 && between(z1, z4, z2)) return 1;
    if (o3 == 0 && between(z3, z1, z4)) return 1;
    if (o4 == 0 && between(z3, z2, z4)) return 1;
    return 0;
}

void solve() {
    ll xl, yl, xr, yr, x1, y1, x2, y2;
    cin >> xl >> yl >> xr >> yr >> x1 >> y1 >> x2 >> y2;
    tie(xl, xr) = minmax(xl, xr);
    tie(yl, yr) = minmax(yl, yr);

    if ((xl <= x1 && x1 <= xr && yl <= y1 && y1 <= yr)
    || (xl <= x2 && x2 <= xr && yl <= y2 && y2 <= yr)) {
        cout << "STOP\n";
        return;
    }

    Complex vertex[4] = {{xl, yl}, {xl, yr}, {xr, yr}, {xr, yl}};
    Complex z1(x1, y1), z2(x2, y2);
    for (int i = 0; i < 4; i++) {
        if (intersect(z1, z2, vertex[i], vertex[(i + 1) % 4])) {
            cout << "STOP\n";
            return;
        }
    }
    cout << "OK\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}