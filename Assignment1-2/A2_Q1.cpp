#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, K;
    std::cout << "Enter N and then " << "K: ";
    std::cin >> N >> K;

    std::vector<int> arr(N);
    std::cout << "Enter " << N << " integers: ";
    for (int& x : arr) std::cin >> x;

    // Total number of subsets = 2^N
    // We iterate every bitmask from 0 (empty set) to 2^N - 1.
    // Bit j of mask being set means arr[j] is IN the subset.

    int totalSubsets = (1 << N);   // 2^N
    int divisibleCount = 0;

    std::cout << "\nAll subsets:\n";
    for (int mask = 0; mask < totalSubsets; ++mask) {
        long long sum = 0;
        std::cout << "{ ";
        for (int j = 0; j < N; ++j) {
            if (mask & (1 << j)) {    // j-th bit is set
                std::cout << arr[j] << " ";
                sum += arr[j];
            }
        }
        std::cout << "} → sum = " << sum;

        if (sum % K == 0) {
            std::cout << "  ✓ divisible by " << K;
            ++divisibleCount;
        }
        std::cout << '\n';
    }

    std::cout << "\nTotal subsets            : " << totalSubsets  << '\n';
    std::cout << "Subsets with sum % " << K << " == 0: "
              << divisibleCount << '\n';

    return 0;
}
