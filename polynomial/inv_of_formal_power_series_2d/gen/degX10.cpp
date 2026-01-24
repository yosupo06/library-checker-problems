#include "random.h"
#include "../params.h"
#include <cstdio>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n=10;
    int m=NM_MAX/n;
    
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int lo = (i == 0 && j == 0) ? 1 : 0;
            int v = gen.uniform<int>(lo, MOD - 1);
            printf("%d", v);
            if (j + 1 < m) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
