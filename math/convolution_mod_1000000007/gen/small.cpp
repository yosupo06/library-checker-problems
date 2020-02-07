#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = seed / 4 + 1;
    int m = seed % 4 + 1;
    vector<int> a(n), b(m);

    for (int i = 0; i < n; i++) {
        a[i] = gen.uniform(0ll, MOD - 1);
    }
    for (int i = 0; i < m; i++) {
        b[i] = gen.uniform(0ll, MOD - 1);
    }

    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < m; i++) {
        printf("%d", b[i]);
        if (i != m - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
