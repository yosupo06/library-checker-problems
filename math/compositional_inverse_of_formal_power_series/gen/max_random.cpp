#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;
    printf("%d\n", n);

    printf("0 %d", gen.uniform(1, int(MOD - 1)));
    for (int i = 2; i < n; i++) {
        printf(" %d", gen.uniform(0, int(MOD - 1)));
    }
    printf("\n");
    return 0;
}
