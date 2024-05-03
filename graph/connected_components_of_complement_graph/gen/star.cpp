#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char **argv) {
    long long seed = atoll(argv[1]);
    Random gen(seed);
    int n = N_MAX;
    int m = n - 1;
    printf("%d %d\n", n, m);
    int center = gen.uniform(0, n - 1);
    for (int i = 0; i < n; ++i) {
        if (i != center) {
            printf("%d %d\n", i, center);
        }
    }
    return 0;
}
