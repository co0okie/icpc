#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, p;
    cin >> n >> p;
    vector<int> S(p), T(p), F(p);
    while (n--) {
        for (int i = 0; i < p; i++) {
            char pm; int att;
            cin >> pm >> att;
            if (pm == '+') {
                S[i]++;
            }
            if (att > 0 || pm == '+') {
                T[i]++;
            }
            F[i] += att;
        }
    }
    for (int j = 0; j < p; j++) {
        cout << S[j] << " " << T[j] << " " << F[j] << "\n";
    }
}