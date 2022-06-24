#include "random.h"
#include <iostream>
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1LL,N_MAX);
    ll q = 0;
    
    printf("%d %lld\n", n, q);
    for (int i = 0; i < n; i++) {
        printf("%d", gen.uniform(0, (int)(MOD) - 1));
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
