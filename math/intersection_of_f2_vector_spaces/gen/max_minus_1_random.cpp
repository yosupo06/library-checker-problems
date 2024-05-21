#include <cstdio>
#include <utility>

#include "random.h"
#include "../params.h"
#include "../binary_mat.h"

std::vector<int> gen_indep(Random &gen, size_t n) {
    BinaryMat mat;
    std::vector<int> res;
    for (size_t i = 0; i < n; ++i) {
        int x;
        do {
            x = gen.uniform(0LL, UV_MAX);
        } while (!mat.is_indep(x));
        mat.add(x);
        res.push_back(x);
    }
    return res;
}

void out(const std::vector<int> &a) {
    size_t n = a.size();
    std::printf("%zu", n);
    for (auto& v: a) std::printf(" %d", v);
    std::printf("\n");
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int T = T_MAX;

    printf("%d\n", T);

    for (int t = 0; t < T; ++t) {
        std::vector<int> u = gen_indep(gen, static_cast<size_t>(NM_MAX - 1));
        out(u);

        std::vector<int> v = gen_indep(gen, static_cast<size_t>(NM_MAX - 1));
        out(v);
    }

    return 0;
}
