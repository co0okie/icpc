#include <bits/stdc++.h>
using namespace std;
int T, n;
string s1, s2;

int match() {
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += s1[i] == s2[i];
    }
    return s;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    while (T--) {
        cin >> n;
        cin >> s1 >> s2;
        cout << match() << " ";
        int maxI, maxJ, maxMatch = -1;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                reverse(s2.begin() + i, s2.begin() + j + 1);
                auto m = match();
                if (m > maxMatch || m == maxMatch && (
                    j - i < maxJ - maxI || j - i == maxJ - maxI && i < maxI
                )) {
                    // cout << "<before: " << maxMatch << " " << maxI << " " << maxJ << ">";
                    maxMatch = m;
                    maxI = i;
                    maxJ = j;
                    // cout << "<after: " << maxMatch << " " << maxI << " " << maxJ << ">";
                }
                reverse(s2.begin() + i, s2.begin() + j + 1);
            }
        }
        cout << maxMatch << " " << maxI + 1 << " " << maxJ + 1 << '\n';
    }
}