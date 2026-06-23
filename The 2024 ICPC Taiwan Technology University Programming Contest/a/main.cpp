#include <iostream>
#include <vector>

using namespace std;

int main() {
	int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int n;
        cin >> n;
        int max, max_diff_left, max_diff_right;
        for (int j = 0; j < n; j++) {
            int income;
            cin >> income;
            if (j == 0) {
                max = income; 
                max_diff_left = income;
                continue;
            }
            if (j == 1) max_diff_right = income;
            if (max - income > max_diff_left - max_diff_right) {
                max_diff_left = max;
                max_diff_right = income;
            }
            if (income > max) max = income;
        }
        cout << max_diff_left << " - " << max_diff_right << endl;
    }
    return 0;
}
