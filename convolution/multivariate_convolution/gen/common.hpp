#pragma once

#include <vector>
#include "random.h"

std::vector<int> rand_vec(const std::vector<int> &ns, Random& gen, int mod) {
    int N = 1;
    for (int n : ns) N *= n;
    std::vector<int> v(N);
    for (int i = 0; i < N; i++) {
        v[i] = gen.uniform(0, mod - 1);
    }
    return v;
}
