#include <bits/stdc++.h>
using namespace std;
int main() {
    int a[3];
    cin >> a[0] >> a[1] >> a[2];
    sort(a, a + 3);
    if (a[2] - a[0] >= 10) {
        cout << "check again\n";
    } else {
        cout << "final " << a[1];
    }
}