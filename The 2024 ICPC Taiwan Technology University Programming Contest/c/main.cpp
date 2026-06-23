#include <iostream>
#include <vector>

using namespace std;

int main() {
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int n;
        cin >> n;
        vector<int> clouds;
        for (int j = 0; j < n; j++) {
            int cloud;
            cin >> cloud;
            clouds.push_back(cloud);
        }
        
        int step = 0;
        for (int pos = 0; pos < n;) {
            if (pos + 2 >= n - 1) {
                step++;
                break;
            }
            if (!clouds[pos + 2]) {
                pos += 2;
                step++;
                continue;
            }
            if (!clouds[pos + 1]) {
                pos += 1;
                step++;
                continue;
            }
            step = -1;
            break;
        }
        cout << step << endl;
    }

    return 0;
}