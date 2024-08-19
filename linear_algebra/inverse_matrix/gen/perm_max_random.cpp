#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(N_MAX - 10, N_MAX);
    vector<vector<int>> a(n, vector<int>(n));
    vector<int> p = gen.perm<int>(n);
    for (int i = 0; i < n; i++) {
        a[i][p[i]] = gen.uniform<int>(0, MOD - 1);
    }

    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", a[i][j]);
            if (j + 1 != n) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
