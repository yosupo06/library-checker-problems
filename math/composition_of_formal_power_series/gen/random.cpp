#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1ll,N_MAX);
    vector<int> f(n),g(n);
    for (int i = 0; i < n; i++){
        f[i] = gen.uniform(0ll,MOD-1);
    }
    for (int i = 0; i < n; i++) {
        if(i)g[i] = gen.uniform(0ll,MOD-1);
        else g[i]=0;
    }

    printf("%d\n",n);

    for (int i = 0; i < n; i++) {
        printf("%d", f[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d", g[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    return 0;
}