#include "../params.h"
#include "network.h"

// Even-Tarjan (1975), Network Flow and Testing Graph Connectivity, Section 4,
// pp. 514-516, Figures 1-3 and the dense extension (all capacities are one).
// https://doi.org/10.1137/0204043
// https://www.cs.princeton.edu/courses/archive/fall03/cs528/handouts/network%20flow%20and%20testing.pdf
// Independent implementation. Shift edges precede diagonals and cross-row edges;
// descending source rows force h phases for the reference's forward DFS.
int main(int argc, char* argv[]) {
    const int h = argc > 2 ? std::atoi(argv[2]) : 17;
    const bool dense = argc <= 3 || std::atoi(argv[3]);
    assert(h >= 1);
    Network g(2, 0, 1);
    std::vector<std::vector<int>> a(h + 1), b(h + 1);
    for (int i = 1; i <= h; ++i) {
        a[i] = g.vertices(i);
        b[i] = g.vertices(i);
    }
    for (int i = h; i >= 1; --i) for (int v : a[i]) g.add(g.s, v, 1);
    for (int i = 1; i <= h; ++i) for (int v : b[i]) g.add(v, g.t, 1);
    for (int i = 1; i <= h; ++i) {
        for (int j = 0; j + 1 < i; ++j) g.add(a[i][j], b[i][j + 1], 1);
    }
    for (int i = 1; i <= h; ++i) {
        for (int j = 0; j < i; ++j) g.add(a[i][j], b[i][j], 1);
    }
    if (dense) {
        for (int i = 1; i < h; ++i) for (int j = 0; j < i; ++j) {
            for (int k = i + 1; k <= h; ++k) {
                for (int l = j; l < k; ++l) g.add(a[i][j], b[k][l], 1);
            }
        }
    }
    assert(g.n == h * (h + 1) + 2);
    g.print(N_MAX, M_MAX, C_MAX);
}
