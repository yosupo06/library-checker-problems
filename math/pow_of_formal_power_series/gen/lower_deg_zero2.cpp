// f の定数項が 0 で f^m \neq 0 のテストケースを生成する

#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;
    int q = gen.uniform(1LL, M_MAX);
    
    vector<int> f(n);
    for (int i = 0; i < n; i++) {
        f[i] = gen.uniform(0LL, MOD - 1);
    }
    int m;
    do {
      m = gen.uniform(1, n);
    } while ((long long)(m-1)*q>n-1);
    
    for (int i = 0; i < m; i++) {
        f[i] = 0;
    }

    printf("%d %d\n", n, q);

    for (int i = 0; i < n; i++) {
        printf("%d", f[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
