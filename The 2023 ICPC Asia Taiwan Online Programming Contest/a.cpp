#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    string s;
    cin >> s;
    ll y = stoi(s.substr(0, 4));
    ll m = stoi(s.substr(5, 7));
    ll d = stoi(s.substr(8, 10));
    if (y > 2023) {
        cout << "TOO LATE";
        return 0;
    } else if (y < 2023) {
        cout << "GOOD";
        return 0;
    } else if (m > 9) {
        cout << "TOO LATE";
        return 0;
    } else if (m < 9) {
        cout << "GOOD";
        return 0;
    } else if (d > 30 + 21 - 35) {
        cout << "TOO LATE";
        return 0;
    } else if (d < 30 + 21 - 35) {
        cout << "GOOD";
        return 0;
    }
    cout << "GOOD";
    return 0;
}