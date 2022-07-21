#include "random.h"
#include <iostream>
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;
    ll q = M_MAX;
    int k = gen.uniform(0, (n - 1) / 2) * 2;
    k += seed % 2;
    printf("%d %lld\n", n, q);
    for (int i = 0; i < n; i++) {
        printf("%d", (i == k ? 1 : 0));
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
