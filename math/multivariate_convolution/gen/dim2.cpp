#include <cstdio>
#include "../params.h"
#include "common.hpp"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int l, r;
    if (seed % 2 == 0) {
        l = gen.uniform(2ll, PROD_N_MAX / 2);
    } else {
        l = gen.uniform(2, int(sqrt(PROD_N_MAX)));
    }
    r = PROD_N_MAX / l;
    vector<int> ns = {l, r};
    int k = 2;
    int N = l * r;

    vector<int> f = rand_vec(ns, gen, (int)(MOD));
    vector<int> g = rand_vec(ns, gen, (int)(MOD));

    printf("%d\n", k);
    for (int i = 0; i < k; i++) {
        printf("%d", ns[i]);
        if (i != k - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%d", f[i]);
        if (i != N - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%d", g[i]);
        if (i != N - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
