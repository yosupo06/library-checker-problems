#include "../params.h"
#include "network.h"

// Even-Tarjan (1975), Network Flow and Testing Graph Connectivity, Section 4,
// pp. 516-517, Figure 4: unit edge capacities without unit vertex capacities.
// https://doi.org/10.1137/0204043
// https://www.cs.princeton.edu/courses/archive/fall03/cs528/handouts/network%20flow%20and%20testing.pdf
// Independently constructed. N = 3*h^3 + 2*h^2 + 2; F = h^2.
int main(int argc, char* argv[]) {
    const int h = argc > 2 ? std::atoi(argv[2]) : 4;
    assert(h >= 1);
    const int square = h * h, cube = square * h;
    Network g(2, 0, 1);
    const auto a = g.vertices(cube), b = g.vertices(cube);
    const auto c = g.vertices(square), e = g.vertices(square);
    std::vector<std::vector<int>> layer;
    for (int i = 0; i < square; ++i) layer.push_back(g.vertices(h));
    for (int v : a) g.add(g.s, v, 1);
    for (int v : e) g.add(v, g.t, 1);
    for (int u : a) for (int v : b) g.add(u, v, 1);
    for (int u : b) for (int v : c) g.add(u, v, 1);
    for (int i = 0; i < square; ++i) g.add(c[i], layer[i][0], 1);
    for (int u : layer.back()) for (int v : e) g.add(u, v, 1);
    for (int i = 0; i + 1 < square; ++i) {
        for (int u : layer[i]) for (int v : layer[i + 1]) g.add(u, v, 1);
    }
    assert(g.n == 3 * cube + 2 * square + 2);
    assert(int(g.edges.size()) == cube * cube + cube * square + square * square + 2 * cube + square);
    g.print(N_MAX, M_MAX, C_MAX);
}
