#include "random.h"
#include <iostream>
#include <tuple>

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 200'000;
    int q = 200'000;
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        int x = gen.uniform(0, 1'000'000'000);
        int y = gen.uniform(0, 1'000'000'000);
        int w = gen.uniform(0, 1'000'000'000);
        printf("%d %d %d\n", x, y, w);
    }
    for (int i = 0; i < q; i++) {
        int l, d, r, u;
        tie(l, r) = gen.uniform_pair(0, 1'000'000'000);
        tie(d, u) = gen.uniform_pair(0, 1'000'000'000);
        printf("%d %d %d %d\n", l, d, r, u);
    }
    return 0;
}