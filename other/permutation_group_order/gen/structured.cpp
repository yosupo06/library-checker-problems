#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int, char** argv) {
    long long seed = std::atoll(argv[1]);
    Random random(seed);
    int n = N_MAX;
    std::vector<int> id(n);
    std::iota(id.begin(), id.end(), 0);
    std::vector<std::vector<int>> generators;
    auto cycle = [&](int first, int size) {
        auto p = id;
        for (int i = 0; i < size; ++i) p[first + i] = first + (i + 1) % size;
        return p;
    };
    int type = int(seed % 12);
    if (type == 0) { // Trivial group, with many redundant generators.
        generators.push_back(id);
    } else if (type == 1) { // Symmetric group.
        generators.push_back(cycle(0, n));
        generators.push_back(cycle(0, 2));
    } else if (type == 2) { // Alternating group on 49 points; one fixed point.
        generators.push_back(cycle(0, 49));
        generators.push_back(cycle(0, 3));
    } else if (type == 3) { // Cyclic group with several different cycle lengths.
        auto p = id;
        int first = 0;
        for (int size : {2, 3, 5, 7, 11, 13}) {
            auto q = cycle(first, size);
            for (int j = first; j < first + size; ++j) p[j] = q[j];
            first += size;
        }
        generators.push_back(p);
    } else if (type == 4) { // Dihedral group.
        generators.push_back(cycle(0, n));
        auto p = id;
        for (int i = 0; i < n; ++i) p[i] = (n - i) % n;
        generators.push_back(p);
    } else if (type == 5) { // Independent swaps: C_2^25.
        for (int i = 0; i < n; i += 2) generators.push_back(cycle(i, 2));
    } else if (type == 6) { // Direct product S_25 x S_25.
        for (int first : {0, 25}) {
            generators.push_back(cycle(first, 25));
            generators.push_back(cycle(first, 2));
        }
    } else if (type == 7) { // Diagonal S_25: same orbits as the preceding case.
        for (int size : {25, 2}) {
            auto p = cycle(0, size);
            auto q = cycle(25, size);
            for (int i = 25; i < n; ++i) p[i] = q[i];
            generators.push_back(p);
        }
    } else if (type == 8) { // Imprimitive wreath product C_2 wr S_25.
        generators.push_back(cycle(0, 2));
        auto p = id, q = id;
        for (int i = 0; i < n; ++i) p[i] = (i + 2) % n;
        for (int i = 0; i < 4; ++i) q[i] = i ^ 2;
        generators.push_back(p);
        generators.push_back(q);
    } else if (type == 9) { // Regular quaternion group on 8 points.
        // Encoding: 1, i, j, k, -1, -i, -j, -k.
        auto p = id, q = id;
        int left_i[] = {1, 4, 3, 6, 5, 0, 7, 2};
        int left_j[] = {2, 7, 4, 1, 6, 3, 0, 5};
        for (int i = 0; i < 8; ++i) {
            p[i] = left_i[i];
            q[i] = left_j[i];
        }
        generators.push_back(p);
        generators.push_back(q);
    } else if (type == 10) { // Affine group AGL(5,2) on 32 points.
        auto p = id, q = id, r = id;
        for (int i = 0; i < 32; ++i) {
            p[i] = ((i << 1) & 31) | (i >> 4);
            q[i] = i ^ ((i & 1) << 1);
            r[i] = i ^ 1;
        }
        generators = {p, q, r};
    } else { // A symmetric group supported only on the last few points.
        generators.push_back(cycle(43, 7));
        generators.push_back(cycle(43, 2));
    }
    if (seed >= 12) {
        auto relabel = id;
        random.shuffle(relabel.begin(), relabel.end());
        for (auto& p : generators) {
            auto q = id;
            for (int i = 0; i < n; ++i) q[relabel[i]] = relabel[p[i]];
            p = q;
        }
        int count = int(generators.size());
        while (int(generators.size()) < K_MAX) {
            auto p = generators[random.uniform(0, count - 1)];
            generators.push_back(p);
        }
        random.shuffle(generators.begin(), generators.end());
    }
    std::printf("%d %d\n", n, int(generators.size()));
    for (const auto& p : generators) {
        for (int i = 0; i < n; ++i) std::printf("%d%c", p[i], i + 1 == n ? '\n' : ' ');
    }
}
