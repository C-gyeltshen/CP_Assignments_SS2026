
#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <algorithm>   // std::reverse, std::accumulate
#include <numeric>     // std::accumulate
#include <iterator>    // std::ostream_iterator


static void separator(const std::string& title) {
    std::cout << "\n===== " << title << " =====\n";
}

// ── Part (a)
void part_a() {
    separator("Part A – vector reversed");

    int N;
    std::cout << "Enter N: ";
    std::cin >> N;

    std::vector<int> vec(N);
    std::cout << "Enter " << N << " integers: ";
    for (int& x : vec) std::cin >> x;

    // Reverse using STL reverse iterator (no extra memory)
    std::cout << "Reversed: ";
    std::copy(vec.rbegin(), vec.rend(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // Alternative: std::reverse in-place (shown for completeness)
    // std::reverse(vec.begin(), vec.end());
}

// ── Part (b): 
void part_b() {
    separator("Part B – deque operations");

    std::deque<int> dq;

    // Simulate a fixed sequence of operations
    // Format: 'F x' = push_front x | 'B x' = push_back x | 'P' = pop_front
    std::vector<std::pair<char,int>> ops = {
        {'B', 10}, {'B', 20}, {'F', 5},
        {'B', 30}, {'P', 0 }, {'F', 1},
        {'B', 40}, {'P', 0 }
    };

    std::cout << "Executing operations:\n";
    for (auto& [op, val] : ops) {
        if (op == 'B') {
            dq.push_back(val);
            std::cout << "  push_back(" << val << ")\n";
        } else if (op == 'F') {
            dq.push_front(val);
            std::cout << "  push_front(" << val << ")\n";
        } else {
            if (!dq.empty()) {
                std::cout << "  pop_front()  → removed " << dq.front() << '\n';
                dq.pop_front();
            }
        }
    }

    std::cout << "Deque contents: ";
    for (const int x : dq) std::cout << x << " ";
    std::cout << '\n';
}

// ── Part (c): 
void part_c() {
    separator("Part C – std::array sum");

    // Fixed size known at compile time
    constexpr std::size_t SIZE = 8;
    std::array<int, SIZE> arr = {3, 7, 1, 9, 4, 6, 2, 8};

    std::cout << "Array elements: ";
    for (const int x : arr) std::cout << x << " ";
    std::cout << '\n';

    // std::accumulate from <numeric>
    int total = std::accumulate(arr.begin(), arr.end(), 0);
    std::cout << "Sum (std::accumulate): " << total << '\n';
}

// ── main ──────────────────────────────────────────────────────
int main() {
    part_a();
    part_b();
    part_c();
    return 0;
}
