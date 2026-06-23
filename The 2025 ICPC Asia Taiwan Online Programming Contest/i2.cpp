#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    // Optimize C++ IO operations
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    std::cin >> n >> q;

    // We use 1-based indexing to match the problem statement
    // Use long long to be safe with pressure values and counts
    std::vector<long long> p(n + 1);
    std::vector<long long> current_pressure(n + 1, 0);
    std::vector<long long> vent_counts(n + 1, 0);

    // Read initial maximum pressure limits
    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i];
    }

    // Process each operation
    for (int op_num = 0; op_num < q; ++op_num) {
        int op;
        std::cin >> op;

        if (op == 1) {
            // Type 1: Pressure Increase Operation
            int l, r;
            long long k;
            std::cin >> l >> r >> k;

            // Iterate through the specified range and apply the pressure increase
            for (int i = l; i <= r; ++i) {
                current_pressure[i] += k;

                // Check if the reactor needs to vent
                if (current_pressure[i] >= p[i]) {
                    long long p_old = p[i]; // Store old p for update
                    
                    current_pressure[i] = 0; // Reset pressure
                    vent_counts[i]++;        // Increment vent count
                    
                    // Update the maximum pressure limit
                    p[i] = std::max(p_old / 2, 1LL); // Use 1LL for long long
                }
            }
        } else if (op == 2) {
            // Type 2: Venting Count Query
            int l, r;
            std::cin >> l >> r;

            long long total_vents = 0;
            // Sum the vent counts in the specified range
            for (int i = l; i <= r; ++i) {
                total_vents += vent_counts[i];
            }
            
            // Print the result for the query
            std::cout << total_vents << "\n";
        }
    }

    return 0;
}
