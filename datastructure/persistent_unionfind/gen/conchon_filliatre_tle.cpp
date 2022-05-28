#include <cassert>
#include <iostream>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>

#include "../params.h"
#include "random.h"
using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = gen.uniform<int>(MAX_N, MAX_N);
    int Q = gen.uniform<int>(MAX_Q, MAX_Q);
    Q = 4 * (Q / 4);
    N = std::max(N, Q / 2 + 20);

    printf("%d %d\n", N, Q);

    for (int i = 0; i < Q / 2; ++i)
        printf("0 %d %d %d\n", i - 1, gen.uniform(0, 19), i + 20);
    for (int i = 0; i < Q / 4; ++i) {
        auto u = gen.uniform<int>(0, N - 1);
        int v;
        do {
            v = gen.uniform<int>(0, N - 1);
        } while (u == v);
        printf("1 -1 %d %d\n", u, v);
        u = gen.uniform<int>(0, N - 1);
        do {
            v = gen.uniform<int>(0, N - 1);
        } while (u == v);
        printf("1 %d %d %d\n", Q / 2 - 1, u, v);
    }

    return 0;
}
