#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char **argv) {
    long long seed = atoll(argv[1]);
    Random gen(seed);
    int n = N_MAX;
    int m = n - 2;
    printf("%d %d\n", n, m);
    auto [center, partner] = gen.uniform_pair(0, n - 1);
    for (int i = 0; i < n; ++i) {
        if (i != center && i != partner) {
            printf("%d %d\n", i, center);
        }
    }
    return 0;
}
