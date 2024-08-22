#include "random.h"
#include <iostream>

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500'000;
    int q = 500'000;
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        int a = gen.uniform(1, 998244352);
        int b = gen.uniform(0, 998244352);
        printf("%d %d\n", a, b);
    }
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 1);
        printf("%d ", t);
        if (t == 0) {
            int p = gen.uniform(0, n - 1);
            int c = gen.uniform(1, 998244352);
            int d = gen.uniform(0, 998244352);
            printf("%d %d %d\n", p, c, d);
        } else {
            auto p = gen.uniform_pair(0, n);
            int x = gen.uniform(0, 998244352);
            printf("%d %d %d\n", p.first, p.second, x);
        }
    }
    return 0;
}
