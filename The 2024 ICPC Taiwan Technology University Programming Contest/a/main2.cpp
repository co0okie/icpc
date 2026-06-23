#include <iostream>
#include <vector>

using namespace std;

int main() {
	int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int n;
        cin >> n;
        vector<int> incomes;
        int max, max_diff_left = -9999999, max_diff_right = 0;
        for (int j = 0; j < n; j++) {
            int income;
            cin >> income;
            incomes.push_back(income);
        }
        for (int j = 0; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (incomes[j] - incomes[k] > max_diff_left - max_diff_right) {
                    max_diff_left = incomes[j];
                    max_diff_right = incomes[k];
                }
            }
        }
        cout << max_diff_left << " - " << max_diff_right << endl;
    }
    return 0;
}
