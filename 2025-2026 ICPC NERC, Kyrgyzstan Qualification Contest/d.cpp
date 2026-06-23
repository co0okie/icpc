#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll n, q, k;
    string lan;
    cin >> n >> q >> k >> lan;
    ll op_count;
    if (lan == "cpp") {
        op_count = 5'0000'0000;
    } else if (lan == "java") op_count = 1'0000'0000;
    else op_count = 20'000'000;

    bool tl = 0, ml = 0;
    if (n * (2 * q + 5 * k) > op_count) tl = 1;
    if (n * k > 20'000'000) ml = 1;
    if (ml && tl) cout << "TL and ML";
    else if (ml && !tl) cout << "ML";
    else if (!ml && tl) cout << "TL";
    else cout << "OK";
}