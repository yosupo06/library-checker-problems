#include <cstdio>
#include "../params.h"
#include "common.hpp"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int k = 0;
    int N = 1;

    vector<int> f = rand_vec({}, gen, (int)(MOD));
    vector<int> g = rand_vec({}, gen, (int)(MOD));

    printf("%d\n", k);
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
