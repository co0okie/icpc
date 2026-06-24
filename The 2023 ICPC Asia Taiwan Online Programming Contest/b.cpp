#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ll rt, rj, st, sj;
    double dst, dsj;
    cin >> rt >> rj >> dst >> dsj;
    st = round(100 * dst);
    sj = round(100 * dsj);
    ll t = (rt - 1) * sj;
    ll j = (rj - 1) * st;
    if (t == j) cout << "SAME";
    else if (t < j) cout << "TAOYUAN";
    else if (t > j) cout << "JAKARTA";
    return 0;
}