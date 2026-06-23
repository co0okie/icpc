#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        string s, sj, sk;
        cin >> s;
        int j, k;
        cin >> j >> k;
        do {
            j--; k--;
            if (j == 0) {
                sj = s;
            }
            if (k == 0) {
                sk = s;
            }
            if (j <= 0 && k <= 0) break;
        } while (next_permutation(s.begin(), s.end()));
        
        int A = 0;
        for (int i = 0; i < s.size(); i++) {
            if (sj[i] == sk[i]) {
                A++;
            }
        }
        cout << A << "A" << s.size() - A << "B\n";
    }
}