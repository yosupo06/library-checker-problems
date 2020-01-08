#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 500000);
    int q = gen.uniform(1, 500000);
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        printf("%d", gen.uniform(0, 1'000'000'000));
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < q; i++) {
        auto p = gen.uniform_pair(0, n);
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}
