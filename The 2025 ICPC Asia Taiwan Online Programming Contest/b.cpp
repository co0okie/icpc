#include <bits/stdc++.h>
using namespace std;
#define ll long long


bool isPrime(ll x) {
    if (x == 1) return false;
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll t;
    cin >> t;

    for (ll _ = 0; _ < t; _++) {
        ll a, b;
        cin >> a >> b;
        if (a + 2 != b) {
            cout << "N" << endl;
            continue;
        }
        if (isPrime(a) && isPrime(b)) {
            cout << "Y" << endl;
        } else {
            cout << "N" << endl;
        }
    }

    return 0;
}