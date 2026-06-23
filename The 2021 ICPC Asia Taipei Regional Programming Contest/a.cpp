#include <bits/stdc++.h>
using namespace std;

int main() {
    int t, x, y, n;
    cin >> t;
    while (t--) {
        cin >> x >> y >> n;
        auto m = *ranges::partition_point(views::iota(1, n), [&](int i) {
            return i + i / x * y < n;
        });
        cout << m * 3 << endl;
    }
}