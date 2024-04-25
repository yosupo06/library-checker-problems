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

std::vector<int> randomize_basis(Random &gen, const std::vector<int> &basis) {
    BinaryMat mat;
    std::vector<int> res;
    while (res.size() < basis.size()) {
        int x;
        do {
            x = 0;
            for (int b: basis) {
                if (gen.uniform(0, 1)) {
                    x ^= b;
                }
            }
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

    int T = 0;
    for (size_t n = 0; n <= NM_MAX; ++n) {
        for (size_t m = 0; m <= NM_MAX; ++m) {
            for (size_t k = std::max(size_t{30}, n + m) - 30; k <= std::min(n, m); k++) {
                T++;
            }
        }
    }
    // T = 5456
    int per_nmk = 18;
    T *= per_nmk; // T = 98208
    printf("%d\n", T);

    for (size_t n = 0; n <= NM_MAX; ++n) {
        for (size_t m = 0; m <= NM_MAX; ++m) {
            for (size_t k = std::max(size_t{30}, n + m) - 30; k <= std::min(n, m); k++) {
                for (int case_nr = 0; case_nr < per_nmk; ++case_nr) {
                    std::vector<int> uni = gen_indep(gen, n + m - k);
                    std::vector<int> u(n), v(m);
                    for (size_t i = 0; i < k; ++i) {
                        u[i] = uni[i];
                        v[i] = uni[i];
                    }
                    for (size_t i = k; i < n; ++i) {
                        u[i] = uni[i];
                    }
                    for (size_t i = k; i < m; ++i) {
                        v[i] = uni[i + n - k];
                    }
                    u = randomize_basis(gen, u);
                    v = randomize_basis(gen, v);
                    out(u);
                    out(v);
                    T++;
                }
            }
        }
    }

    return 0;
}
