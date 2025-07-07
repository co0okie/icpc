#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    while (!cin.eof()) {
        int M;
        cin >> M;
        string as;
        getline(cin, as);
        getline(cin, as);
        stringstream ass{as};
        vector<vector<int>> Ls{M};
        int a;
        while (ass >> a) {
            Ls[a % M].push_back(a);
            // cout << a << " ";
        }
        // cout << endl;
        for (vector<int>& L : Ls) {
            sort(L.begin(), L.end());
            for (int a : L) {
                cout << a << " ";
            }
        }
        cout << endl;
    }

    return 0;
}

