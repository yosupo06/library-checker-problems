#include "../params.h"
#include "network.h"
#include <array>

// Queyranne (1980): https://doi.org/10.1287/moor.5.2.258
// Weininger's repeated-gadget construction (CC0):
// https://codeforces.com/blog/entry/145343
// https://github.com/leonard-weininger/worst-case-max-flow/blob/9d1c94b32cb38c6116a8e1d5a42038a2ba320496/generators/gen_anti_most_improving.cpp
// Each gadget requires 3*k widest-path augmentations, with decreasing
// Fibonacci bottlenecks. Its maximum flow is fib[3*k+2] - 1.
int main(int argc, char* argv[]) {
    Random rng(std::atoll(argv[1]));
    const int k = argc > 3 ? std::atoi(argv[2]) : 14;
    const int copies = argc > 3 ? std::atoi(argv[3]) : 588;
    assert(1 <= k && k <= 14 && copies >= 1);
    std::array<long long, 45> fib{};
    fib[1] = 1;
    for (int i = 2; i < int(fib.size()); ++i) fib[i] = fib[i - 1] + fib[i - 2];
    std::array<long long, 5> capacity{};
    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j < 3; ++j) capacity[j] += fib[3 * i - 2 + j];
    }
    capacity[3] = fib[3 * k];
    capacity[4] = fib[3 * k + 1];
    // (tail, head, capacity group) in the ten-vertex gadget.
    const std::array<std::array<int, 3>, 17> edges = {{
        {0,5,0}, {5,6,0}, {1,2,0}, {7,8,0}, {3,9,0},
        {0,6,1}, {1,7,1}, {2,3,1}, {8,9,1},
        {0,1,2}, {6,7,2}, {2,8,2}, {3,4,2}, {4,9,2},
        {1,6,3}, {8,3,3}, {7,2,4}
    }};
    Network g(8 * copies + 2, 0, 8 * copies + 1);
    for (int i = 0; i < copies; ++i) {
        std::array<int, 10> v{};
        v[0] = g.s;
        v[9] = g.t;
        for (int j = 1; j <= 8; ++j) v[j] = 8 * i + j;
        for (auto e : edges) g.add(v[e[0]], v[e[1]], capacity[e[2]]);
    }
    assert(int(g.edges.size()) == 17 * copies);
    g.permute_vertices(rng);
    g.print(N_MAX, M_MAX, C_MAX);
}
