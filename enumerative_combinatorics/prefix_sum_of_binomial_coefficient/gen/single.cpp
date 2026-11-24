#include <cstdio>
#include <cstdlib>
#include "../params.h"

int main(int, char* argv[]) {
    long long seed = std::atoll(argv[1]);
    int n = seed == 0 ? 0 : N_MAX;
    int k = seed == 1 ? n / 2 : seed == 2 ? n : 0;
    printf("1\n%d %d\n", n, k);
}
