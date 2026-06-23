#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, s;
    char dir;
    cin >> n >> s >> dir;

    int a, b, c;
    if (dir == 'L') {
        a = b = (s + 1) / 2;
        c = n - s;
    } else {
        a = s - 1;
        b = c = (n - s) / 2 + 1;
    }
    cout << a << " " << b << " " << c;
}