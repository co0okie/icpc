#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll x, d;
    cin >> x >> d;
    if (2 * x > d) {
        cout << "take it";
    } else {
        cout << "double it";
    }
    return 0;
}
